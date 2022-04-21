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
    m_ecs.RegisterComponent(Transform());
    m_ecs.RegisterComponent(Renderable());
    m_ecs.RegisterComponent(Value());
    m_ecs.RegisterComponent(Tag());
    m_ecs.RegisterComponent(Collider());

    m_playerEntity = m_ecs.CreateEntity();
    m_ecs.SetComponent(m_playerEntity, Renderable(sf::Color::Blue));
    m_ecs.SetComponent(m_playerEntity, Transform(0.0f, 0.0f));

    for (int i = 1; i < MAX_ENTITIES; i++)
    {
        Entity entity = m_ecs.CreateEntity();

        if (i % 2 == 0)
        {
            m_ecs.SetComponent(entity, Tag(Tags::BAD));
            m_ecs.SetComponent(entity, Renderable(sf::Color::Red));
        }
        else
        {
            m_ecs.SetComponent(entity, Tag(Tags::GOOD));
            m_ecs.SetComponent(entity, Renderable(sf::Color::Green));
            m_ecs.SetComponent(entity, Transform(0.0f));
        }

        m_ecs.SetComponent(entity, Collider(m_ecs.GetComponentArray<Renderable>().at(entity).shape.getRadius()));
    }
}

void Game::Update(const float& dt)
{
    Renderable& playerRend = m_ecs.GetComponentArray<Renderable>().at(m_playerEntity);
    Value& playerScore = m_ecs.GetComponentArray<Value>().at(m_playerEntity);
    playerRend.shape.setRadius(static_cast<float>(playerScore.worth));

    Transform& transform = m_ecs.GetComponentArray<Transform>().at(m_playerEntity);
    Collider& collider = m_ecs.GetComponentArray<Collider>().at(m_playerEntity);
    collider.collider.width = playerScore.worth;
    collider.collider.height = playerScore.worth;


    transform.velocity = { 0.0f, 0.0f };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
            transform.velocity.y = -100.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
            transform.velocity.y = 100.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
            transform.velocity.x = -100.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
            transform.velocity.x = 100.0f;
    }

    transform.position.x += transform.velocity.x * dt;
    transform.position.y += transform.velocity.y * dt;
    transform.velocity = { 0.0f, 0.0f };
    //playerRend.shape.setPosition(transform.position);


#if MULTITHREADING
    m_ecs.ForEach_mult<Transform, Collider>([&](Entity& entity, Transform& transform, Collider& collider)
#else
    m_ecs.ForEach<Transform, Collider>([&](Entity& entity, Transform& transform, Collider& collider)
#endif
        {
            transform.position.x += transform.velocity.x * dt;
            transform.position.y += transform.velocity.y * dt;

            collider.collider.left = transform.position.x;
            collider.collider.top = transform.position.y;
        }
    );


#if MULTITHREADING
    m_ecs.ForEach_mult<Collider, Tag>([&](Entity& entity, Collider& rend, Tag& tag)
#else
    m_ecs.ForEach<Collider, Tag>([&](Entity& entity, Collider& rend, Tag& tag)
#endif
        {
            if (rend.canCollide == 1)
            {
                if (IsColliding(rend.collider, collider.collider))
                {
                    switch (tag.tag)
                    {
                    case Tags::GOOD:
                    {
                        playerScore.worth++;
                        rend.canCollide = 0;
                        break;
                    }
                    case Tags::BAD:
                    {
                        playerScore.worth--;
                        rend.canCollide = 0;
                        break;
                    }
                    default:
                        break;
                    }

                    if (playerScore.worth < 1)
                        playerScore.worth = 1;

                }
            }
        });

    SFMLTon::GetView().setCenter(playerRend.shape.getPosition() + vec2(playerRend.shape.getRadius(), playerRend.shape.getRadius()));
    SFMLTon::GetWindow().setView(SFMLTon::GetView());
}

void Game::Draw()
{
    SFMLTon::GetWindow().clear();
    m_ecs.ForEach<Renderable, Transform, Collider>([&](Entity entity, Renderable& rend, Transform& transform, Collider& coll)
        {
            rend.shape.setPosition(transform.position);

            if(coll.canCollide)
                SFMLTon::GetWindow().draw(rend.shape);
        });
    SFMLTon::GetWindow().display();
}
bool Game::IsColliding(const sf::FloatRect& first, const sf::FloatRect& second)
{
    return first.intersects(second);
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

#if MULTITHREADING
    #pragma omp parallel for schedule(static)
#endif
    for (int i = 1; i < (int)m_objects.size(); i++)
    {
        // Move the object.
        m_objects[i]->Move(dt);
    }

#if MULTITHREADING
    #pragma omp parallel for schedule(static)
#endif
    for (int i = 1; i < (int)m_objects.size(); i++)
    {
        if (m_player.IsColliding(*m_objects[i]))
        {
            switch (m_objects[i]->GetTag())
            {
            case Tags::BAD:
            {
                m_player.RemovePoints(1);
                m_objects.erase(m_objects.begin() + i);
                break;
            }
            case Tags::GOOD:
            {
                m_player.AddPoints(1);
                m_objects.erase(m_objects.begin() + i);
                break;
            }
            default:
                break;
            }

            m_player.UpdateScale();
        }
    }


    vec2 center = { m_player.GetPosition().x + m_player.GetScale().x, m_player.GetPosition().y + m_player.GetScale().y };

    SFMLTon::GetView().setCenter(center);
    SFMLTon::GetWindow().setView(SFMLTon::GetView());
}

void Game::Draw()
{
    SFMLTon::GetWindow().clear();
    for (int i = 0; i < (int)m_objects.size(); i++)
    {
        SFMLTon::GetWindow().draw(*m_objects[i]);
    }
    SFMLTon::GetWindow().display();
}

#endif