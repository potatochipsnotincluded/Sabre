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

	void TransformComponent::RenderImGui(TransformComponent& self, Project& project)
	{
		if (ImGui::CollapsingHeader("Transform Component"))
		{
			InputVec3("Position ", (int32_t)(&self.Position), 0.001f, self.Position);
			InputVec3("Rotation ", (int32_t)(&self.Rotation), 0.001f, self.Rotation);
			InputVec3("Scale ", (int32_t)(&self.Scale), 0.001f, self.Scale);
		}
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


}
