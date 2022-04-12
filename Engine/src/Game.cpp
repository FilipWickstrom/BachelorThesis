#include "PCH.h"
#include "Game.h"
#include "Components.h"

static sf::CircleShape firstShape(1.0f);
static sf::CircleShape secondShape(1.0f);

Game::Game()
{
    m_playerEntity = 0;
}

Game::~Game()
{
}

void Game::Init()
{
    m_coordinator.Init();
    m_coordinator.RegisterComponent<Transform>();
    m_coordinator.RegisterComponent<Color>();
    m_coordinator.RegisterComponent<Value>();
    m_coordinator.RegisterComponent<Moveable>();
    m_coordinator.RegisterComponent<Tag>();
    m_coordinator.RegisterComponent<Renderable>();


    m_renderSystem = m_coordinator.RegisterSystem<RenderSystem>();
    m_movementSystem = m_coordinator.RegisterSystem<MovementSystem>();
    m_collisionSystem = m_coordinator.RegisterSystem<CollisionSystem>();

    Signature rendSignature;
    rendSignature.set(m_coordinator.GetComponentType<Renderable>());
    m_coordinator.SetSystemSignature<RenderSystem>(rendSignature);

    Signature moveSignature;
    moveSignature.set(m_coordinator.GetComponentType<Moveable>());
    //moveSignature.set(m_coordinator.GetComponentType<Enemy>());
    m_coordinator.SetSystemSignature<MovementSystem>(moveSignature);

    Signature collSignature;
    collSignature.set(m_coordinator.GetComponentType<Transform>());
    m_coordinator.SetSystemSignature<CollisionSystem>(collSignature);

    m_entities.resize(MAX_ENTITIES);

    Entity player = m_coordinator.CreateEntity();
    m_coordinator.AddComponent(player, Transform());
    m_coordinator.AddComponent(player, Value());
    m_coordinator.AddComponent(player, Tag(Tags::PLAYER));
    m_coordinator.AddComponent(player, Moveable());
    m_coordinator.AddComponent(player, Renderable(sf::Color::Blue));
    m_entities[0] = player;
    m_playerEntity = player;

    for (Entity entity = 1; entity < MAX_ENTITIES; entity++)
    {
        entity = m_coordinator.CreateEntity();

        m_coordinator.AddComponent(entity, Transform());

        if (entity % 2 == 0)
        {
            m_coordinator.AddComponent(entity, Tag(Tags::BAD));
            m_coordinator.AddComponent(entity, Moveable());
            m_coordinator.AddComponent(entity, Renderable(sf::Color::Red));
        }
        else
        {
            m_coordinator.AddComponent(entity, Tag(Tags::GOOD));
            m_coordinator.AddComponent(entity, Renderable(sf::Color::Green));
        }

        
        m_coordinator.AddComponent(entity, Value());
        m_entities[entity] = entity;
    }
}



void Game::Update(const float& dt)
{
    //m_movementSystem->Update(m_coordinator, dt);

    //m_collisionSystem.get()->Detect(m_playerEntity, m_coordinator);
    //m_collisionSystem.get()->Act(m_coordinator);

    const Renderable& playerTransf = m_coordinator.GetComponent<Renderable>(m_playerEntity);
    SFMLTon::GetView().setCenter(playerTransf.shape.getPosition());
    SFMLTon::GetWindow().setView(SFMLTon::GetView());

    //for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
    //{
    //    Transform& transf = m_coordinator.GetComponent<Transform>(entity);
    //    transf.position.x += transf.velocity.x * dt;
    //    transf.position.y += transf.velocity.y * dt;
    //}

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        Transform& transf = m_transforms[i];
        transf.position.x += transf.velocity.x * dt;
        transf.position.y += transf.velocity.y * dt;
    }

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        Transform& transf = m_transforms[i];
        transf.position.x += transf.velocity.x * dt;
        transf.position.y += transf.velocity.y * dt;
    }
}



void Game::Draw()
{
    SFMLTon::GetWindow().clear();

    //m_renderSystem->Render(m_coordinator);

    SFMLTon::GetWindow().display();

}
