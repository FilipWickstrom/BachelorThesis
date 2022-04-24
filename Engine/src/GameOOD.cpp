#include "PCH.h"
#include "GameOOD.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
#include "FoodObject.h"

GameOOD::GameOOD()
{
	//Add a player
	std::unique_ptr<GameObject> player = std::make_unique<PlayerObject>();
	player->SetPosition({ WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f });
	m_gameobjects.push_back(std::move(player));
	m_playerID = static_cast<uint>(m_gameobjects.size() - 1);

	//Add some enemies
	for (uint i = 0; i < NR_OF_ENEMIES; i++)
	{
		std::unique_ptr<GameObject> enemy = std::make_unique<EnemyObject>();
		m_gameobjects.push_back(std::move(enemy));
	}

	//Add some food - randomizes if good or bad
	for (uint i = 0; i < NR_OF_FOOD; i++)
	{
		std::unique_ptr<GameObject> food = std::make_unique<FoodObject>();
		m_gameobjects.push_back(std::move(food));
	}

	m_gameOver = false;
}

void GameOOD::Update(const float& dt)
{
	if (m_gameOver) return;

	PlayerObject* playerObj = dynamic_cast<PlayerObject*>(m_gameobjects.at(m_playerID).get());

	// Collision check
	for (size_t i = 0; i < m_gameobjects.size(); i++)
	{
		GameObject* currentObj = m_gameobjects.at(i).get();
		//Safety check
		if (!currentObj) return;

		currentObj->Update(dt);

		if (playerObj->IsColliding(*currentObj))
		{
			switch (currentObj->GetTag())
			{
			case ETagType::enemy:
			{
				playerObj->ResetPoints();
				break;
			}
			case ETagType::goodfood:
			case ETagType::badfood:
			{
				FoodObject* food = dynamic_cast<FoodObject*>(currentObj);
				//Add points to player
				playerObj->AddPoints(food->GetWorth());

				//Check winconditions for players
				if (playerObj->CheckWinCondition())
				{
#if DRAW_GAME
					WINDOW.setTitle("You win the game!");
#endif
					m_gameOver = true;
				}

				//Remove object
				m_gameobjects.erase(m_gameobjects.begin() + i);
				break;
			}
			default:
				break;
			};
		}
	}
}

void GameOOD::Render()
{
	WINDOW.clear();

	for (const auto& obj : m_gameobjects)
		obj->Render();

	WINDOW.setView(SFMLTon::GetCamera());
	WINDOW.display();
}
