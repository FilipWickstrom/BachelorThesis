#pragma once
#include <EntityManager.h>
#include <Components.h>
#include <System.h>

class Coordinator
{
private:

	Coordinator();
	~Coordinator();

	static auto& Get()
	{
		static Coordinator instance;
		return instance;
	}

	ComponentManager m_componentManager;
	EntityManager m_entityManager;
	SystemManager m_systemManager;

public:

	static Entity CreateEntity();

	static void DestroyEntity(const Entity& entity);

	template<typename T>
	static std::shared_ptr<T> RegisterSystem()
	{
		return Coordinator::Get().m_systemManager.RegisterSystem<T>();
	}

	template<typename T>
	static void SetSystemSignature(const Signature& signature)
	{
		Coordinator::Get().m_systemManager.SetSignature<T>(signature);
	}

	template<typename T>
	static void RegisterComponent()
	{
		Coordinator::Get().m_componentManager.RegisterComponent<T>();
	}

	template<typename T>
	static void AddComponent(const Entity& entity, T component)
	{
		Coordinator::Get().m_componentManager.AddComponent<T>(entity, component);

		auto signature = Coordinator::Get().m_entityManager.GetSignature(entity);
		signature.set(Coordinator::Get().m_componentManager.GetComponentType<T>(), true);
		Coordinator::Get().m_entityManager.SetSignature(entity, signature);

		Coordinator::Get().m_systemManager.EntitySigantureChanged(entity, signature);
	}

	template<typename T>
	static void RemoveComponent(const Entity& entity)
	{
		Coordinator::Get().m_componentManager.RemoveComponent<T>(entity);

		auto signature = Coordinator::Get().m_entityManager.GetSignature(entity);
		signature.set(Coordinator::Get().m_componentManager.GetComponentType<T>(), false);
		Coordinator::Get().m_entityManager.SetSignature(entity, signature);

		Coordinator::Get().m_systemManager.EntitySigantureChanged(entity, signature);
	}

	template<typename T>
	static T& GetComponent(const Entity& entity)
	{
		return Coordinator::Get().m_componentManager.GetComponent<T>(entity);
	}

	template<typename T>
	static ComponentType GetComponentType()
	{
		return Coordinator::Get().m_componentManager.GetComponentType<T>();
	}
};