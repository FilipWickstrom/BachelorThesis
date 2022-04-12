#pragma once
#include "EntityManager.h"
#include "Components.h"
#include "System.h"

class Coordinator
{
private:

	ComponentManager m_componentManager;
	EntityManager m_entityManager;
	SystemManager m_systemManager;

public:

	Coordinator();
	~Coordinator();

	Entity CreateEntity();

	void DestroyEntity(const Entity& entity);

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return m_systemManager.RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(const Signature& signature)
	{
		m_systemManager.SetSignature<T>(signature);
	}

	template<typename T>
	void RegisterComponent()
	{
		m_componentManager.RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(const Entity& entity, T component)
	{
		m_componentManager.AddComponent<T>(entity, component);

		auto signature = m_entityManager.GetSignature(entity);
		signature.set(m_componentManager.GetComponentType<T>(), true);
		m_entityManager.SetSignature(entity, signature);

		m_systemManager.EntitySigantureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(const Entity& entity)
	{
		m_componentManager.RemoveComponent<T>(entity);

		auto signature = m_entityManager.GetSignature(entity);
		signature.set(m_componentManager.GetComponentType<T>(), false);
		m_entityManager.SetSignature(entity, signature);

		m_systemManager.EntitySigantureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(const Entity& entity)
	{
		return m_componentManager.GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return m_componentManager.GetComponentType<T>();
	}
};