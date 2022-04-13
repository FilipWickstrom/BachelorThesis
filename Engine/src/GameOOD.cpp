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
}

void GameOOD::GetObjectsWithTag(const ETagType& tag, std::vector<uint>& vec)
{
	for (uint i = 0; i < static_cast<uint>(m_gameobjects.size()); i++)
	{
		if (m_gameobjects.at(i)->GetTag() == tag)
			vec.push_back(i);
	}
	vec.shrink_to_fit();
}

void GameOOD::Update(const float& dt)
{
	//Update every object - mostly movement
	for (auto& obj : m_gameobjects)
		obj->Update(dt);

	std::vector<uint> enemies;
	std::vector<uint> allfood;
	GetObjectsWithTag(ETagType::enemy, enemies);
	GetObjectsWithTag(ETagType::goodfood, allfood);
	GetObjectsWithTag(ETagType::badfood, allfood);
	bool playerHasCollided = false;

	//Player info
	GameObject* currentPlayer = m_gameobjects.at(m_playerID).get();
	PlayerObject* playerObj = dynamic_cast<PlayerObject*>(currentPlayer);

	for (uint i = 0; i < static_cast<uint>(allfood.size()); i++)
	{
		uint foodID = allfood.at(i);
		GameObject* currentFood = m_gameobjects.at(foodID).get();

		if (playerObj->IsColliding(*currentFood))
		{
			playerHasCollided = true;
			FoodObject* food = dynamic_cast<FoodObject*>(currentFood);
			//Add points to player
			playerObj->SetPoints(food->GetWorth());

			//Check winconditions for players
			if (playerObj->CheckWinCondition())
			{
				WINDOW.setTitle("You won the game!");
			}

			//Remove the food and tell garbage collector to clean up
			m_gameobjects.at(foodID)->SetTag(ETagType::garbage);
		}
	}

	for (uint i = 0; i < static_cast<uint>(enemies.size()); i++)
	{
		uint enemyID = enemies.at(i);
		GameObject* currentEnemy = m_gameobjects.at(enemyID).get();

		if (playerObj->IsColliding(*currentEnemy))
		{
			playerObj->SetPoints(-playerObj->GetMaxPoints());
		}
	}
	
	//Player did not collide. Just end/stop it now!
	if (!playerHasCollided) return;


	//Garbage collector
	for (size_t i = 0; i < m_gameobjects.size(); i++)
	{
		if (m_gameobjects.at(i)->GetTag() == ETagType::garbage)
			m_gameobjects.erase(m_gameobjects.begin() + i);
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
