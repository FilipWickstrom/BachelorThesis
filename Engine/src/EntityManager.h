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

	void DestroyEntity(Entity entity);

	void SetSignature(Entity entity, const Signature& signature);

	Signature GetSignature(Entity entity);
};