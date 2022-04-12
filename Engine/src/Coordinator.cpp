#include "PCH.h"
#include "Coordinator.h"

Coordinator::Coordinator()
{
    m_entityManager = std::make_unique<EntityManager>();
    m_componentManager = std::make_unique<ComponentManager>();
    m_systemManager = std::make_unique<SystemManager>();
}

Coordinator::~Coordinator()
{
}

Entity Coordinator::CreateEntity()
{
    return m_entityManager->CreateEntity();
}

void Coordinator::DestroyEntity(Entity entity)
{
    m_entityManager->DestroyEntity(entity);
    m_componentManager->EntityDestroyed(entity);
    m_systemManager->EntityDestroyed(entity);
}
