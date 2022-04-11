#pragma once


class System
{
public:
	std::set<Entity> m_entities;
};

class SystemManager
{
private:

	std::unordered_map<const char*, Signature> m_signatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};

public:

	SystemManager() = default;

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(m_systems.find(typeName) == m_systems.end() && "System already exists.");

		auto system = std::make_shared<T>();
		m_systems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	void SetSignature(const Signature& signature)
	{
		const char* typeName = typeid(T).name();

		assert(m_systems.find(typeName) != m_systems.end() && "System doesn't exist.");

		m_signatures.insert({ typeName, signature });
	}

	void EntityDestroyed(const Entity& entity)
	{
		for (auto const& pair : m_systems)
		{
			auto const& system = pair.second;

			system->m_entities.erase(entity);
		}
	}

	void EntitySigantureChanged(const Entity& entity, const Signature& entitySignature)
	{
		for (auto const& pair : m_systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& signature = m_signatures[type];

			if ((entitySignature & signature) == signature)
			{
				system->m_entities.insert(entity);
			}
			else
			{
				system->m_entities.erase(entity);
			}
		}
	}
};

// Systems

class MovementSystem : public System
{
public:

	void Update(const float& dt);

};

class RenderSystem : public System
{
public:

	void Draw();
};

class CollisionSystem : public System
{
private:

	std::vector<Entity> m_collisions;

public:

	void Detect();
	void Act();
};