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

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        Entity entity = m_ecs.CreateEntity();
    }
}

void Game::Update(const float& dt)
{
    m_ecs.ForEach_mult<Transform, Renderable>([&](Transform& transform, Renderable& rend)
        {
            transform.position.x += transform.velocity.x * dt;
            transform.position.y += transform.velocity.y * dt;
            rend.shape.setPosition(transform.position);
        }
    );
}

void Game::Draw()
{
    SFMLTon::GetWindow().clear();
    m_ecs.ForEach<Renderable>([&](Renderable& rend)
        {
            SFMLTon::GetWindow().draw(rend.shape);
        });
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
    for (int i = 0; i < (int)m_objects.size(); i++)
    {
        SFMLTon::GetWindow().draw(*m_objects[i]);
    }
}

#endif