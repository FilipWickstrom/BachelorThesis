#include "PCH.h"
#include "Game.h"
#include "Components.h"


#ifdef DOD
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
    SFMLTon::GetWindow().clear();
    SFMLTon::GetWindow().display();

}
#endif

#ifdef OOD

Game::Game()
{

}

Game::~Game()
{
    while ((int)m_objects.size() > 1)
    {
        delete m_objects[(int)m_objects.size() - 1];
        m_objects.pop_back();
    }
}

void Game::Init()
{
    // Init player.
    m_player.SetTag(Tags::PLAYER);
    m_objects.push_back(&m_player);

    for (int i = 0; i < MAX_OBJECTS - 1; i++)
    {
        if (i % 2 == 0)
        {
            FoodObject* foodObject = new FoodObject();
            m_objects.push_back(foodObject);
        }
        else
        {
            EnemyObject* enemyObject = new EnemyObject();
            m_objects.push_back(enemyObject);
        }
    }
}

void Game::Update(const float& dt)
{
    m_player.Move(dt);

    for (int i = 1; i < (int)m_objects.size(); i++)
    {
        // Move the object.
        m_objects[i]->Move(dt);


        if (m_player.IsColliding(*m_objects[i]))
        {
            switch (m_objects[i]->GetTag())
            {
            case Tags::BAD:
            {
                m_player.RemovePoints(1);
                break;
            }
            case Tags::GOOD:
            {
                m_player.AddPoints(1);
                break;
            }
            default:
                break;
            }

            m_player.UpdateScale();
        }
    }

    SFMLTon::GetView().setCenter(m_player.GetPosition());
    SFMLTon::GetWindow().setView(SFMLTon::GetView());
}

void Game::Draw()
{
    for (int i = 0; i < (int)m_objects.size(); i++)
    {
        SFMLTon::GetWindow().draw(*m_objects[i]);
    }
}

#endif