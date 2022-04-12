#include "PCH.h"
#include "Game.h"
#include "Coordinator.h"

Game::Game()
{
}

void Game::Init()
{
    Coordinator::RegisterComponent<Transform>();
    Coordinator::RegisterComponent<Color>();
    Coordinator::RegisterComponent<Tag>();
    Coordinator::RegisterComponent<Value>();
    Coordinator::RegisterComponent<Collider>();

    m_renderSystem = Coordinator::RegisterSystem<RenderSystem>();
    m_movementSystem = Coordinator::RegisterSystem<MovementSystem>();
    m_collisionSystem = Coordinator::RegisterSystem<CollisionSystem>();

    Signature rendSignature;
    rendSignature.set(Coordinator::GetComponentType<Transform>());
    rendSignature.set(Coordinator::GetComponentType<Color>());
    rendSignature.set(Coordinator::GetComponentType<Tag>());
    Coordinator::SetSystemSignature<RenderSystem>(rendSignature);

    Signature moveSignature;
    moveSignature.set(Coordinator::GetComponentType<Transform>());
    moveSignature.set(Coordinator::GetComponentType<Tag>());
    Coordinator::SetSystemSignature<MovementSystem>(moveSignature);

    Signature collSignature;
    collSignature.set(Coordinator::GetComponentType<Collider>());
    Coordinator::SetSystemSignature<CollisionSystem>(collSignature);

    m_entities.resize(MAX_ENTITIES);

    Entity player = Coordinator::CreateEntity();
    Coordinator::AddComponent(player, Transform());
    Coordinator::AddComponent(player, Tag(Tags::PLAYER));
    Coordinator::AddComponent(player, Color(sf::Color::Blue));
    Coordinator::AddComponent(player, Value(1));
    Coordinator::AddComponent(player, Collider());
    m_entities[0] = player;
    m_playerEntity = player;

    for (Entity entity = 1; entity < MAX_ENTITIES; entity++)
    {
        entity = Coordinator::CreateEntity();

        Coordinator::AddComponent(entity, Transform());

        if (entity % 2 == 0)
        {
            Coordinator::AddComponent(entity, Tag(Tags::BAD));
            Coordinator::AddComponent(entity, Color(sf::Color::Red));
        }
        else
        {
            Coordinator::AddComponent(entity, Tag(Tags::GOOD));
            Coordinator::AddComponent(entity, Color(sf::Color::Green));
        }

        Coordinator::AddComponent(entity, Collider());
        Coordinator::AddComponent(entity, Value(1));
        m_entities[entity] = entity;
    }
}



void Game::Update(const float& dt)
{
    m_collisionSystem.get()->Detect(m_playerEntity);
    m_movementSystem.get()->Update(dt);

    m_collisionSystem.get()->Act();

    std::cout << "FPS: " << 1.0f / dt << "\n";

    if (Coordinator::GetComponent<Value>(m_playerEntity).worth > 25)
    {
        Coordinator::DestroyEntity(m_playerEntity);
        SFMLTon::GetWindow().setTitle("YOU WON!");
    }
    else
    {
        SFMLTon::GetWindow().setTitle("Score: " + std::to_string(Coordinator::GetComponent<Value>(m_playerEntity).worth) + " FPS: " + std::to_string(1.0f / dt));
    }
}

void Game::Draw()
{
    SFMLTon::GetWindow().clear();

    m_renderSystem.get()->Draw();

    SFMLTon::GetWindow().display();

}
