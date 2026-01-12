#include "ECS.h"
namespace Sabre {

	template<typename T, typename... Args>
	inline void Scene::AddComponent(Entity entity, Args&&... args)
	{
		Registry.emplace<T>(entity.Handle, std::forward<Args>(args)...);
	}

	template<typename T>
	inline void Scene::RemoveComponent(Entity entity)
	{
		Registry.remove<T>(entity.Handle);
	}

	template<typename T>
	inline T& Scene::GetComponent(Entity entity)
	{
		return Registry.get<T>(entity.Handle);
	}

	template<typename T>
	inline bool Scene::HasComponent(Entity entity)
	{
		auto view = Registry.view<T>();

		return view.contains(entity.Handle);
	}

}
