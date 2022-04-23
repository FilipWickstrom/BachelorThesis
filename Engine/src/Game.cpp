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
    m_ecs.SetComponent(m_playerEntity, Tag(Tags::PLAYER));
    m_ecs.SetComponent(m_playerEntity, Renderable(sf::Color::Blue, 10.f));
    m_ecs.SetComponent(m_playerEntity, Transform(0.f));
    m_ecs.SetComponent(m_playerEntity, Collider(10.f));

    for (int i = 1; i < MAX_ENTITIES; i++)
    {
        Entity entity = m_ecs.CreateEntity();

        if (i % 2 == 0)
        {
            m_ecs.SetComponent(entity, Tag(Tags::BAD));
            m_ecs.SetComponent(entity, Renderable(sf::Color::Red, 10.f));
            m_ecs.SetComponent(entity, Collider(10.f));
        }
        else
        {
            m_ecs.SetComponent(entity, Tag(Tags::GOOD));
            m_ecs.SetComponent(entity, Renderable(sf::Color::Green, 10.f));
            m_ecs.SetComponent(entity, Transform(0.f));
            m_ecs.SetComponent(entity, Collider(10.f));
        }
    }
}

void Game::Update(const float& dt)
{
    Renderable& playerRend      = m_ecs.GetComponentArray<Renderable>().at(m_playerEntity);
    Value&      playerScore     = m_ecs.GetComponentArray<Value>().at(m_playerEntity);
    Transform&  playerTransform = m_ecs.GetComponentArray<Transform>().at(m_playerEntity);
    Collider&   playerCollider  = m_ecs.GetComponentArray<Collider>().at(m_playerEntity);


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        playerTransform.velocity.y = -100.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerTransform.velocity.y = 100.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerTransform.velocity.x = -100.0f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerTransform.velocity.x = 100.0f;
    }

    playerTransform.position.x += playerTransform.velocity.x * dt;
    playerTransform.position.y += playerTransform.velocity.y * dt;
    playerTransform.velocity = { 0.0f, 0.0f };

    // Use this loop instead to include Renderable.

//#if MULTITHREADING
//    m_ecs.ForEach_mult<Transform, Renderable, Collider>([&](Entity& entity, Transform& transform, Renderable& rend, Collider& collider)
//#else
//    m_ecs.ForEach<Transform, Renderable, Collider>([&](Entity& entity, Transform& transform, Renderable& rend, Collider& collider)
//#endif
//        {
//            transform.position.x += transform.velocity.x * dt;
//            transform.position.y += transform.velocity.y * dt;
//            rend.shape.setPosition(transform.position);
//            collider.position.x = transform.position.x + collider.radius;
//            collider.position.y = transform.position.y + collider.radius;
//        }
//    );


#if MULTITHREADING
    m_ecs.ForEach_mult<Transform, Collider>([&](Entity& entity, Transform& transform, Collider& collider)
#else
    m_ecs.ForEach<Transform, Collider>([&](Entity& entity, Transform& transform, Collider& collider)
#endif
        {
            transform.position.x += transform.velocity.x * dt;
            transform.position.y += transform.velocity.y * dt;

            collider.position.x = transform.position.x + collider.radius;
            collider.position.y = transform.position.y + collider.radius;
        }
    );


#if MULTITHREADING
    m_ecs.ForEach_mult<Tag, Collider>([&](Entity& entity, Tag& tag, Collider& collider)
#else
    m_ecs.ForEach<Tag, Collider>([&](Entity& entity, Tag& tag, Collider& collider)
#endif
        {
            if (collider.canCollide == 1)
            {
                //Avoid collision between player and itself
                if (tag.tag == Tags::PLAYER) return;

                if (IsColliding(playerCollider.position, collider.position,
                                playerCollider.radius, collider.radius))
                {
                    switch (tag.tag)
                    {
                    case Tags::GOOD:
                    {
                        playerScore.worth++;
                        collider.canCollide = 0;
                        break;
                    }
                    case Tags::BAD:
                    {
                        //Score is anything but 0
                        if (playerScore.worth)
                            playerScore.worth--;
                        collider.canCollide = 0;
                        break;
                    }
                    default:
                        break;
                    }

                    float rad = playerScore.worth + 10.f;   //10.f is default size of player
                    playerRend.shape.setRadius(rad);
                    playerCollider.radius = rad;
                    //SFMLTon::GetWindow().setTitle("Points: " + std::to_string(playerScore.worth));
                }
            }
        });


    SFMLTon::GetView().setCenter(playerTransform.position + vec2(playerCollider.radius, playerCollider.radius));
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

bool Game::IsColliding(const vec2& pos1, const vec2& pos2, const float& rad1, const float& rad2)
{
    float xdist = pos2.x - pos1.x;
    float ydist = pos2.y - pos1.y;
    float distance = std::sqrt(xdist * xdist + ydist * ydist);

    if (distance < rad1 + rad2)
        return true;

    return false;
}
#endif

#ifdef OOD

Game::Game()
{

}

Game::~Game()
{
    for (size_t i = 0; i < m_objects.size(); i++)
    {
        delete m_objects.at(i);
    }
}

void Game::Init()
{
    // Init player.
    m_player = new PlayerObject();
    m_player->SetTag(Tags::PLAYER);
    m_objects.push_back(m_player);

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
    m_player->Move(dt);

#if MULTITHREADING
    #pragma omp parallel for schedule(static)
#endif
    for (int i = 1; i < (int)m_objects.size(); i++)
    {
        // Move the object.
        m_objects[i]->Move(dt);

        if (m_player->IsColliding(*m_objects[i]))
        {
            switch (m_objects[i]->GetTag())
            {
            case Tags::BAD:
            {
                m_player->RemovePoints(1);
                m_objects.erase(m_objects.begin() + i);
                break;
            }
            case Tags::GOOD:
            {
                m_player->AddPoints(1);
                m_objects.erase(m_objects.begin() + i);
                break;
            }
            default:
                break;
            }

            m_player->UpdateScale();
        }
    }

    vec2 center = { m_player->GetPosition().x + m_player->GetScale().x, m_player->GetPosition().y + m_player->GetScale().y };
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