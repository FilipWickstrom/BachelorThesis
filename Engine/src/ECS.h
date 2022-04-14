#pragma once
#include "Components.h"
#include "ComponentArray.h"

#ifdef DOD
class ECS
{
private:

	std::queue<Entity> m_availableEntities;
	std::vector<Entity> m_activeEntities;

	std::unordered_map<size_t, std::shared_ptr<IComponentArray>> m_componentArrays{};

public:
	ECS();
	~ECS() = default;

	Entity CreateEntity();
	void DestroyEntity(const Entity& entity);

	std::vector<Entity>& GetActiveEntities();

	template<typename T>
	void RegisterComponent(const T& component)
	{
		size_t type = typeid(T).hash_code();

		assert(m_componentArrays.find(type) != m_componentArrays.end() && "Component already exists.");

		m_componentArrays.insert({ type, std::make_shared<ComponentArray<T>>() });

	}

	template<typename T>
	CompArray<T>& GetComponentArray() const
	{
		size_t type = typeid(T).hash_code();

		assert(m_componentArrays.find(type) == m_componentArrays.end() && "Component doesn't exist");

		return dynamic_cast<ComponentArray<T>*>(m_componentArrays.at(type).get())->GetArray();
	}

	template<typename T>
	void View(std::function<void(T& component)> func)
	{
		// Assert that component actually exists.
		size_t type = typeid(T).hash_code();
		assert(m_componentArrays.find(type) == m_componentArrays.end() && "Component doesn't exist");

		// Get component array.
		CompArray<T>& compArr = this->GetComponentArray<T>();

		// do function over each component.
		for (T& comp : compArr)
		{
			func(comp);
		}
	}

};
#endif
