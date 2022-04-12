#include "PCH.h"
#include "Game.h"
#include "Components.h"
#include "ECS.h"

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
    Entity player = ECS::CreateEntity();
    ECS::Get().m_tags[player] = Tags::PLAYER;
    ECS::Get().m_renderables[player].shape.setFillColor(sf::Color::Blue);

    for (Entity entity = 1; entity < MAX_ENTITIES; entity++)
    {
        Entity newEnt = ECS::CreateEntity();

        if (entity % 2 == 0)
        {
            // Bad
            ECS::Get().m_renderables[newEnt].shape.setFillColor(sf::Color::Red);
            ECS::Get().m_tags[newEnt].tag = Tags::BAD;
        }
        else
        {
            // Good
            ECS::Get().m_renderables[newEnt].shape.setFillColor(sf::Color::Green);
            ECS::Get().m_tags[newEnt].tag = Tags::GOOD;
        }
    }



    //m_coordinator.Init();
    //m_coordinator.RegisterComponent<Transform>();
    //m_coordinator.RegisterComponent<Color>();
    //m_coordinator.RegisterComponent<Value>();
    //m_coordinator.RegisterComponent<Moveable>();
    //m_coordinator.RegisterComponent<Tag>();
    //m_coordinator.RegisterComponent<Renderable>();


    //m_renderSystem = m_coordinator.RegisterSystem<RenderSystem>();
    //m_movementSystem = m_coordinator.RegisterSystem<MovementSystem>();
    //m_collisionSystem = m_coordinator.RegisterSystem<CollisionSystem>();

    //Signature rendSignature;
    //rendSignature.set(m_coordinator.GetComponentType<Renderable>());
    //m_coordinator.SetSystemSignature<RenderSystem>(rendSignature);

    //Signature moveSignature;
    //moveSignature.set(m_coordinator.GetComponentType<Moveable>());
    ////moveSignature.set(m_coordinator.GetComponentType<Enemy>());
    //m_coordinator.SetSystemSignature<MovementSystem>(moveSignature);

    //Signature collSignature;
    //collSignature.set(m_coordinator.GetComponentType<Transform>());
    //m_coordinator.SetSystemSignature<CollisionSystem>(collSignature);

    //m_entities.resize(MAX_ENTITIES);

    //Entity player = m_coordinator.CreateEntity();
    //m_coordinator.AddComponent(player, Transform());
    //m_coordinator.AddComponent(player, Value());
    //m_coordinator.AddComponent(player, Tag(Tags::PLAYER));
    //m_coordinator.AddComponent(player, Moveable());
    //m_coordinator.AddComponent(player, Renderable(sf::Color::Blue));
    //m_entities[0] = player;
    //m_playerEntity = player;

    //for (Entity entity = 1; entity < MAX_ENTITIES; entity++)
    //{
    //    entity = m_coordinator.CreateEntity();

    //    m_coordinator.AddComponent(entity, Transform());

    //    if (entity % 2 == 0)
    //    {
    //        m_coordinator.AddComponent(entity, Tag(Tags::BAD));
    //        m_coordinator.AddComponent(entity, Moveable());
    //        m_coordinator.AddComponent(entity, Renderable(sf::Color::Red));
    //    }
    //    else
    //    {
    //        m_coordinator.AddComponent(entity, Tag(Tags::GOOD));
    //        m_coordinator.AddComponent(entity, Renderable(sf::Color::Green));
    //    }

    //    
    //    m_coordinator.AddComponent(entity, Value());
    //    m_entities[entity] = entity;
    //}
}



void Game::Update(const float& dt)
{
    std::vector<Entity>& entities = ECS::GetActiveEntities();
    Renderable& playerRenderable = ECS::Get().m_renderables[m_playerEntity];

    //SFMLTon::GetWindow().clear();
    // Loop through each entity.
    for (Entity entity : entities)
    {
        Transform& transform = ECS::Get().m_transforms[entity];
        transform.position.x += transform.velocity.x * dt;
        transform.position.y += transform.velocity.y * dt;

        Renderable& renderable = ECS::Get().m_renderables[entity];
        renderable.shape.setPosition(transform.position);

        if (renderable.shouldRender == 1)
        {
            //SFMLTon::GetWindow().draw(renderable.shape);

            // Collision check between player and entity.
            if (playerRenderable.shape.getGlobalBounds().intersects(renderable.shape.getGlobalBounds()))
            {
                Tag& tags = ECS::Get().m_tags[entity];

                switch (tags.tag)
                {
                case Tags::GOOD:
                {
                    ECS::Get().m_values[m_playerEntity].worth++;
                    ECS::Get().m_renderables[entity].shouldRender = 0;
                    break;
                }
                case Tags::BAD:
                {
                    ECS::Get().m_values[m_playerEntity].worth = 0;
                    break;
                }
                default:
                    break;
                }

            }
        }
    }

    // Player movement.
    
    Transform& playerTransf = ECS::Get().m_transforms[m_playerEntity];
    playerTransf.velocity = { 0.0f, 0.0f };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        playerTransf.velocity.x += 100.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        playerTransf.velocity.x -= 100.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        playerTransf.velocity.y -= 100.0f;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        playerTransf.velocity.y += 100.0f;
    playerTransf.position.x += playerTransf.velocity.x * dt;
    playerTransf.position.y += playerTransf.velocity.y * dt;

    // Update position.
    playerRenderable.shape.setPosition(playerTransf.position);

    // Render.
    SFMLTon::GetView().setCenter({ playerTransf.position.x + playerTransf.scale.x, playerTransf.position.y + playerTransf.scale.y });
    //SFMLTon::GetWindow().draw(playerRenderable.shape);
    SFMLTon::GetWindow().setView(SFMLTon::GetView());
    //SFMLTon::GetWindow().display();
}



void Game::Draw()
{
    

    //m_renderSystem->Render(m_coordinator);

    SFMLTon::GetWindow().display();

}
