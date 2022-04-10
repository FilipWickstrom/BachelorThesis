#include "PCH.h"
#include "EntityManager.h"


EntityManager::EntityManager()
{
	for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
	{
		m_entities.push(entity);
	}
}

Entity EntityManager::CreateEntity()
{
	assert(m_activeEntities < MAX_ENTITIES && "Too many entities active!");

	Entity ent = m_entities.front();
	m_entities.pop();
	m_activeEntities++;

	return ent;
}

void EntityManager::DestroyEntity(const Entity& entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");

	m_signatures[entity].reset();

	m_entities.push(entity);
	m_activeEntities--;
}

void EntityManager::SetSignature(const Entity& entity, const Signature& signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");

	m_signatures[entity] = signature;
}

Signature EntityManager::GetSignature(const Entity& entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range");

	return m_signatures[entity];
}
