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

    CompArray<Transform> test = m_ecs.GetComponentArray<Transform>();
}

void Game::Update(const float& dt)
{

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