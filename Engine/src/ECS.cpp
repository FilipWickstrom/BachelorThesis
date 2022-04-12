#include "PCH.h"
#include "ECS.h"

std::queue<Entity> ECS::m_availableEntities = {};
std::vector<Entity> ECS::m_activeEntities = {};
std::array<Transform, MAX_ENTITIES> ECS::m_transforms = {};
std::array<Renderable, MAX_ENTITIES> ECS::m_renderables = {};
std::array<Tag, MAX_ENTITIES> ECS::m_tags = {};
std::array<Value, MAX_ENTITIES> ECS::m_values = {};

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
	Entity ent = Get().m_availableEntities.front();
	Get().m_availableEntities.pop();
	Get().m_activeEntities.push_back(ent);
	return ent;
}

void ECS::DestroyEntity(const Entity& entity)
{
	Get().m_activeEntities.erase(m_activeEntities.begin() + entity);
	Get().m_availableEntities.push(entity);
}

std::vector<Entity>& ECS::GetActiveEntities()
{
	return Get().m_activeEntities;
}

