#pragma once

class EntityManager
{
private:

	std::queue<Entity> m_entities{};
	std::array<Signature, MAX_ENTITIES> m_signatures{};

	std::uint32_t m_activeEntities{};

public:

	EntityManager();

	Entity CreateEntity();

	void DestroyEntity(const Entity& entity);

	void SetSignature(const Entity& entity, const Signature& signature);

	Signature GetSignature(const Entity& entity);
};