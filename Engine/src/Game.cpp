#include "PCH.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
    m_coordinator.RegisterComponent<Transform>();
    m_coordinator.RegisterComponent<Color>();
    m_coordinator.RegisterComponent<Tag>();
    m_coordinator.RegisterComponent<Value>();
    m_coordinator.RegisterComponent<Collider>();

    m_renderSystem = m_coordinator.RegisterSystem<RenderSystem>();
    m_movementSystem = m_coordinator.RegisterSystem<MovementSystem>();
    m_collisionSystem = m_coordinator.RegisterSystem<CollisionSystem>();

    Signature rendSignature;
    rendSignature.set(m_coordinator.GetComponentType<Transform>());
    rendSignature.set(m_coordinator.GetComponentType<Color>());
    rendSignature.set(m_coordinator.GetComponentType<Tag>());
    m_coordinator.SetSystemSignature<RenderSystem>(rendSignature);

    Signature moveSignature;
    moveSignature.set(m_coordinator.GetComponentType<Transform>());
    moveSignature.set(m_coordinator.GetComponentType<Tag>());
    m_coordinator.SetSystemSignature<MovementSystem>(moveSignature);

    Signature collSignature;
    collSignature.set(m_coordinator.GetComponentType<Collider>());
    m_coordinator.SetSystemSignature<CollisionSystem>(collSignature);

    m_entities.resize(MAX_ENTITIES);

    Entity player = m_coordinator.CreateEntity();
    m_coordinator.AddComponent(player, Transform());
    m_coordinator.AddComponent(player, Tag(Tags::PLAYER));
    m_coordinator.AddComponent(player, Color(sf::Color::Blue));
    m_coordinator.AddComponent(player, Value(1));
    m_coordinator.AddComponent(player, Collider());
    m_entities[0] = player;
    m_playerEntity = player;

    for (Entity entity = 1; entity < MAX_ENTITIES; entity++)
    {
        entity = m_coordinator.CreateEntity();

        m_coordinator.AddComponent(entity, Transform());

        if (entity % 2 == 0)
        {
            m_coordinator.AddComponent(entity, Tag(Tags::BAD));
            m_coordinator.AddComponent(entity, Color(sf::Color::Red));
        }
        else
        {
            m_coordinator.AddComponent(entity, Tag(Tags::GOOD));
            m_coordinator.AddComponent(entity, Color(sf::Color::Green));
        }

        m_coordinator.AddComponent(entity, Collider());
        m_coordinator.AddComponent(entity, Value(1));
        m_entities[entity] = entity;
    }
}



void Game::Update(const float& dt)
{
    m_collisionSystem.get()->Detect(m_playerEntity, m_coordinator);
    m_movementSystem.get()->Update(dt, m_coordinator);
    m_collisionSystem.get()->Act(m_coordinator);

    //if (m_coordinator.GetComponent<Value>(m_playerEntity).worth > 25)
    //{
    //    m_coordinator.DestroyEntity(m_playerEntity);
    //    SFMLTon::GetWindow().setTitle("YOU WON!");
    //}
    //else
    //{
    //    SFMLTon::GetWindow().setTitle("Score: " + std::to_string(m_coordinator.GetComponent<Value>(m_playerEntity).worth) + " FPS: " + std::to_string(1.0f / dt));
    //}
}

void Game::Draw()
{
    SFMLTon::GetWindow().clear();

    m_renderSystem.get()->Draw(m_coordinator);

    SFMLTon::GetWindow().display();

}
