#include "PCH.h"
#include "ECS.h"

#ifdef DOD
ECS::ECS()
{
	for (Entity i = 0; i < MAX_ENTITIES; i++)
	{
		m_availableEntities.push(i);
	}

	m_activeEntities.reserve(MAX_ENTITIES);
}

Entity ECS::CreateEntity()
{
	Entity ent = m_availableEntities.front();
	m_availableEntities.pop();
	m_activeEntities.push_back(ent);
	return ent;
}

void ECS::DestroyEntity(const Entity& entity)
{
	m_activeEntities.erase(m_activeEntities.begin() + entity);
	m_availableEntities.push(entity);
}

std::vector<Entity>& ECS::GetActiveEntities()
{
	return m_activeEntities;
}
#endif
