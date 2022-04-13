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
    Entity player = m_ecs.CreateEntity();
    m_ecs.tags[player] = Tags::PLAYER;
    m_ecs.renderables[player].shape.setFillColor(sf::Color::Blue);

    for (Entity entity = 1; entity < MAX_ENTITIES; entity++)
    {
        Entity newEnt = m_ecs.CreateEntity();

        if (entity % 2 == 0)
        {
            // Bad
            m_ecs.renderables[newEnt].shape.setFillColor(sf::Color::Red);
            m_ecs.tags[newEnt].tag = Tags::BAD;
        }
        else
        {
            // Good
            m_ecs.renderables[newEnt].shape.setFillColor(sf::Color::Green);
            m_ecs.tags[newEnt].tag = Tags::GOOD;
        }
    }
}



void Game::Update(const float& dt)
{
    std::vector<Entity>& entities = m_ecs.GetActiveEntities();
    Renderable& playerRenderable = m_ecs.renderables[m_playerEntity];

    //SFMLTon::GetWindow().clear();
    // Loop through each entity.
    for (Entity entity : entities)
    {
        Transform& transform = m_ecs.transforms[entity];
        transform.position.x += transform.velocity.x * dt;
        transform.position.y += transform.velocity.y * dt;

        Renderable& renderable = m_ecs.renderables[entity];
        if (renderable.shouldRender)
        {
            //SFMLTon::GetWindow().draw(renderable.shape);

            // Collision check between player and entity.
            if (playerRenderable.shape.getGlobalBounds().intersects(renderable.shape.getGlobalBounds()))
            {
                Tag& tags = m_ecs.tags[entity];

                switch (tags.tag)
                {
                case Tags::GOOD:
                {
                    m_ecs.values[m_playerEntity].worth++;
                    m_ecs.renderables[entity].shouldRender = 0;
                    break;
                }
                case Tags::BAD:
                {
                    m_ecs.values[m_playerEntity].worth = 0;
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
    
    Transform& playerTransf = m_ecs.transforms[m_playerEntity];
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
