#include "PCH.h"
#include "Coordinator.h"

Coordinator::Coordinator()
{
}

Coordinator::~Coordinator()
{
}

Entity Coordinator::CreateEntity()
{
    return Get().m_entityManager.CreateEntity();
}

void Coordinator::DestroyEntity(const Entity& entity)
{
    Get().m_entityManager.DestroyEntity(entity);
    Get().m_componentManager.EntityDestroyed(entity);
    Get().m_systemManager.EntityDestroyed(entity);
}
