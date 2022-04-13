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
        if (renderable.shouldRender)
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

        renderable.shape.setPosition(transform.position);
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
