#pragma once
#include <glm/glm.hpp>
#include <entt.hpp>

#include <unordered_map>
#include <filesystem>

#include "Sabre/Mesh.h"
#include "Sabre/Material.h"
#include "Sabre/Renderer.h"

#include "imgui/imgui.h"

namespace Sabre {

	using UUID = uint32_t;

	class Scene;

	struct Entity
	{
		entt::entity Handle = entt::null;
		Scene* Parent = nullptr;
	};

	struct TransformComponent
	{
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		static void RenderImGui(TransformComponent& self);
	};

	struct TagComponent
	{
		std::string Tag;
	};

	struct MeshComponent
	{		
		Mesh EntityMesh;
		Material EntityMaterial;

		Entity Owner;

		std::string MeshPath; // For editor use only
		std::string TexturePath; // For editor use only

		inline MeshComponent(Entity owner, const std::filesystem::path& meshPath, const std::filesystem::path& albedoPath, float metallic, float smoothness) : EntityMesh(LoadMesh(GetAssetFile(meshPath))), EntityMaterial(GetAssetFile(albedoPath), smoothness, metallic), Owner(owner) {
			MeshPath = meshPath.string();
			TexturePath = albedoPath.string();
		}

		static void RenderImGui(MeshComponent& self);
	};


	class Scene
	{
	public:
		Scene();

		void OnInit();
		void OnUpdate();
		void OnRender();

		Entity AddEntity();
		void DeleteEntity(Entity entity);

		Entity GetEntity(UUID uuid);

		template<typename T, typename... Args>
		void AddComponent(Entity entity, Args&&... args);

		template <typename T>
		void RemoveComponent(Entity entity);

		template <typename T>
		T& GetComponent(Entity entity);

		template <typename T>
		bool HasComponent(Entity entity);

		std::vector<UUID> GetAllEntities();

	public:
		entt::registry Registry;
	private:
		template <typename T>
		void InitComponentType();

		template <typename T>
		void UpdateComponentType();

		template <typename T>
		void RenderComponentType();
	private:
		class RenderSystem
		{
		public:
			void Render(Scene& scene);
		};

		std::unordered_map<UUID, entt::entity> m_EntityUUIDMap;
		RenderSystem m_RenderSystem;
	};
}

#include "Sabre/ECS.inl"