#include "ECS.h"

#include <random>

#include "imgui/imgui.h"

#include "ImGuiHelpers.h"

namespace Sabre {

	using UUID = uint32_t;

	static UUID GenerateUUID()
	{
		static std::mt19937 gen{ std::random_device{}() };
		static std::uniform_int_distribution<UUID> dist;

		return dist(gen);
	}

	Scene::Scene()
	{
	}

	void Scene::OnInit()
	{
	}

	void Scene::OnUpdate()
	{
	}

	void Scene::OnRender()
	{
		m_RenderSystem.Render(*this);
	}

	Entity Scene::AddEntity()
	{
		Entity entity;
		entity.Handle = Registry.create();
		entity.Parent = this;

		UUID uuid = GenerateUUID();
		m_EntityUUIDMap[uuid] = entity.Handle;

		return entity;
	}

	Entity Scene::AddEntityWithUUID(UUID uuid)
	{
		Entity entity;
		entity.Handle = Registry.create();
		entity.Parent = this;

		m_EntityUUIDMap[uuid] = entity.Handle;

		return entity;
	}

	void Scene::DeleteEntity(Entity entity)
	{
		if (entity.Handle == entt::null)
		{
			return;
		}

		// Remove UUID mapping if present
		for (auto it = m_EntityUUIDMap.begin(); it != m_EntityUUIDMap.end(); ++it)
		{
			if (it->second == entity.Handle)
			{
				m_EntityUUIDMap.erase(it);
				break;
			}
		}

		Registry.destroy(entity.Handle);
	}

	Entity Scene::GetEntity(UUID uuid)
	{
		return Entity(m_EntityUUIDMap[uuid], this);
	}

	void Scene::Clear()
	{
		Registry.clear();
		m_EntityUUIDMap.clear();
	}

	void Scene::Serialize(const std::filesystem::path& scenePath, Project& project)
	{
		json j;

		j["SceneSettings"]["ClearColour"] = { ClearColour.r, ClearColour.g, ClearColour.b, ClearColour.a };
		j["SceneSettings"]["Ambient"] = Sabre::GetSunLight()->AmbientIntensity;
		j["SunLight"]["Colour"] = { Sabre::GetSunLight()->Colour.r, Sabre::GetSunLight()->Colour.g, Sabre::GetSunLight()->Colour.b };
		j["SunLight"]["Direction"] = { Sabre::GetSunLight()->Direction.x, Sabre::GetSunLight()->Direction.y, Sabre::GetSunLight()->Direction.z };
		j["SunLight"]["Intensity"] = Sabre::GetSunLight()->Intensity;

		for (Sabre::UUID uuid : GetAllEntities())
		{
			Sabre::Entity entity = GetEntity(uuid);
			auto& tc = GetComponent<Sabre::TagComponent>(entity);
			tc.Serialize(j, uuid, tc);

			auto& trc = GetComponent<Sabre::TransformComponent>(entity);
			trc.Serialize(j, uuid, trc);

			if (HasComponent<Sabre::MeshComponent>(entity))
			{
				auto& mc = GetComponent<Sabre::MeshComponent>(entity);
				mc.Serialize(j, uuid, mc);
			}
		}

		std::ofstream file = std::ofstream(project.FilePath / scenePath);
		file << std::setw(4) << j << std::endl;
	}

	void Scene::Deserialize(const std::filesystem::path& scenePath, Project& project)
	{
		json j;
		std::ifstream i = std::ifstream(project.FilePath / scenePath);
		i >> j;

		Sabre::GetSunLight()->AmbientIntensity = j["SceneSettings"]["Ambient"];
		ClearColour.r = j["SceneSettings"]["ClearColour"][0];
		ClearColour.g = j["SceneSettings"]["ClearColour"][1];
		ClearColour.b = j["SceneSettings"]["ClearColour"][2];
		ClearColour.a = j["SceneSettings"]["ClearColour"][3];

		Sabre::GetSunLight()->Colour.r = j["SunLight"]["Colour"][0];
		Sabre::GetSunLight()->Colour.g = j["SunLight"]["Colour"][1];
		Sabre::GetSunLight()->Colour.b = j["SunLight"]["Colour"][2];

		Sabre::GetSunLight()->Direction.x = j["SunLight"]["Direction"][0];
		Sabre::GetSunLight()->Direction.y = j["SunLight"]["Direction"][1];
		Sabre::GetSunLight()->Direction.z = j["SunLight"]["Direction"][2];
		Sabre::GetSunLight()->Intensity = j["SunLight"]["Intensity"];

		Clear();

		std::vector<std::string> entityList;
		for (auto it = j["Entities"].begin(); it != j["Entities"].end(); ++it)
		{
			entityList.push_back(it.key());
		}

		for (std::string uuidStr : entityList)
		{
			Sabre::UUID uuid = std::stoul(uuidStr);

			Sabre::Entity entity = AddEntityWithUUID(uuid);
			AddComponent<Sabre::TagComponent>(entity, j["Entities"][std::to_string(uuid)]["TagComponent"]["Tag"].get<std::string>());

			AddComponent<Sabre::TransformComponent>(entity, glm::vec3(), glm::vec3(), glm::vec3());
			auto& trc = GetComponent<Sabre::TransformComponent>(entity);
			trc.Position = glm::vec3(
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Position"][0],
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Position"][1],
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Position"][2]
			);

			trc.Rotation = glm::vec3(
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Rotation"][0],
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Rotation"][1],
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Rotation"][2]
			);

			trc.Scale = glm::vec3(
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Scale"][0],
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Scale"][1],
				j["Entities"][std::to_string(uuid)]["TransformComponent"]["Scale"][2]
			);

			if (j["Entities"][std::to_string(uuid)].contains("MeshComponent"))
			{
				AddComponent<Sabre::MeshComponent>(entity, entity, project.FilePath,
					j["Entities"][std::to_string(uuid)]["MeshComponent"]["MeshPath"].get<std::string>(),
					j["Entities"][std::to_string(uuid)]["MeshComponent"]["TexturePath"].get<std::string>(),
					j["Entities"][std::to_string(uuid)]["MeshComponent"]["Metallic"].get<float>(),
					j["Entities"][std::to_string(uuid)]["MeshComponent"]["Smoothness"].get<float>());
			}
		}
	}

	std::vector<UUID> Scene::GetAllEntities()
	{
		std::vector<UUID> entities;
		entities.reserve(m_EntityUUIDMap.size());

		for (const auto& [uuid, handle] : m_EntityUUIDMap)
		{
			entities.push_back(uuid);
		}

		return entities;
	}

	void Scene::RenderSystem::Render(Scene& scene)
	{
		static ShaderProgramme shader(
			GetAssetFile("Assets/Shaders/pbrFragmentShader.glsl"),
			GetAssetFile("Assets/Shaders/pbrVertexShader.glsl")
		);

		scene.Registry.view<TransformComponent, MeshComponent>().each(
			[](auto entity, auto& tc, auto& mc)
			{
				Renderer::RenderMeshPBR(
					mc.EntityMesh,
					shader,
					&mc.EntityMaterial,
					tc.Position,
					tc.Rotation,
					tc.Scale,
					*g_MainCamera
				);
			}
		);
	}

	void TransformComponent::Serialize(json& j, UUID uuid, const TransformComponent& component)
	{
		j["Entities"][std::to_string(uuid)]["TransformComponent"] = {
			{ "Position", { component.Position.x, component.Position.y, component.Position.z } },
			{ "Rotation", { component.Rotation.x, component.Rotation.y, component.Rotation.z } },
			{ "Scale", { component.Scale.x, component.Scale.y, component.Scale.z } }
		};
	}

	void TransformComponent::RenderImGui(TransformComponent& self, Project& project)
	{
		if (ImGui::CollapsingHeader("Transform Component"))
		{
			InputVec3("Position ", (int32_t)(&self.Position), 0.001f, self.Position);
			InputVec3("Rotation ", (int32_t)(&self.Rotation), 0.001f, self.Rotation);
			InputVec3("Scale ", (int32_t)(&self.Scale), 0.001f, self.Scale);
		}
	}

	void MeshComponent::Serialize(json& j, UUID uuid, const MeshComponent& component)
	{
		j["Entities"][std::to_string(uuid)]["MeshComponent"] = {
			{ "MeshPath", component.MeshPath },
			{ "TexturePath", component.TexturePath },
			{ "Smoothness", component.EntityMaterial.Smoothness },
			{ "Metallic", component.EntityMaterial.Metallic }
		};
	}

	void MeshComponent::RenderImGui(MeshComponent& self, Project& project)
	{
		if (ImGui::CollapsingHeader("Mesh Component"))
		{
			ImGui::Text("Mesh Path "); ImGui::SameLine();
			InputChar("###sabmeshpath", &self.MeshPath);

			ImGui::Text("Albedo Path "); ImGui::SameLine();
			InputChar("###sabalbpath", &self.TexturePath);

			if (ImGui::Button("Reload"))
			{
				self.EntityMesh = LoadMesh(project.FilePath / self.MeshPath);
				self.EntityMaterial = Material(project.FilePath / self.TexturePath, self.EntityMaterial.Smoothness, self.EntityMaterial.Metallic);
			}

			ImGui::Text("Smoothness "); ImGui::SameLine();
			ImGui::DragFloat("###sabsmopath", &self.EntityMaterial.Smoothness, 0.01f, 0, 1);

			ImGui::Text("Metallic "); ImGui::SameLine();
			ImGui::DragFloat("###sabmetpath", &self.EntityMaterial.Metallic, 0.01f, 0, 1);
		}
	}

	void TagComponent::Serialize(json& j, UUID uuid, const TagComponent& component)
	{
		j["Entities"][std::to_string(uuid)]["TagComponent"] = {
			{ "Tag", component.Tag }
		};
	}

}
