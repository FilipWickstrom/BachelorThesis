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

    Signature rendSignature;
    rendSignature.set(Coordinator::GetComponentType<Transform>());
    rendSignature.set(Coordinator::GetComponentType<Color>());
    rendSignature.set(Coordinator::GetComponentType<Tag>());
    Coordinator::SetSystemSignature<RenderSystem>(rendSignature);

    Signature moveSignature;
    moveSignature.set(Coordinator::GetComponentType<Transform>());
    moveSignature.set(Coordinator::GetComponentType<Tag>());
    Coordinator::SetSystemSignature<MovementSystem>(moveSignature);

    m_entities.resize(MAX_ENTITIES);

    Entity player = Coordinator::CreateEntity();
    Coordinator::AddComponent(player, Transform());
    Coordinator::AddComponent(player, Tag(Tags::PLAYER));
    Coordinator::AddComponent(player, Color(sf::Color::Blue));
    Coordinator::AddComponent(player, Value());
    m_entities[0] = player;

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

        m_entities[entity] = entity;
    }
}



void Game::Update(const float& dt)
{
    m_movementSystem.get()->Update(dt);

    //std::cout << dt << "\n";
}

void Game::Draw()
{
    SFMLTon::GetWindow().clear();

    m_renderSystem.get()->Draw();

    SFMLTon::GetWindow().display();
}
