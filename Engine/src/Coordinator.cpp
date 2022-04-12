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
    return m_entityManager.CreateEntity();
}

void Coordinator::DestroyEntity(const Entity& entity)
{
    m_entityManager.DestroyEntity(entity);
    m_componentManager.EntityDestroyed(entity);
    m_systemManager.EntityDestroyed(entity);
}
