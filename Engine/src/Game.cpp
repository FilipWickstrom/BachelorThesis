#include "PCH.h"
#include "Game.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
#include "FoodObject.h"

Game::Game()
{
	vec2 centerPos = { WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f};

	//Add a player
	std::unique_ptr<GameObject> player = std::make_unique<PlayerObject>();
	player->SetPosition(centerPos);
	m_gameobjects.push_back(std::move(player));

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

void Game::GetObjectsWithTag(ETagType tag, std::vector<uint>& vec)
{
	for (uint i = 0; i < static_cast<uint>(m_gameobjects.size()); i++)
	{
		if (m_gameobjects.at(i)->GetTag() == tag)
			vec.push_back(i);
	}
	vec.shrink_to_fit();
}

void Game::Update(const float& dt)
{
	//Update every object - mostly movement
	for (auto& obj : m_gameobjects)
		obj->Update(dt);

	std::vector<uint> players;
	std::vector<uint> enemies;
	std::vector<uint> allfood;
	std::vector<uint> removeObjs;
	GetObjectsWithTag(ETagType::player, players);
	GetObjectsWithTag(ETagType::enemy, enemies);
	GetObjectsWithTag(ETagType::goodfood, allfood);
	GetObjectsWithTag(ETagType::badfood, allfood);

	//Collision check for player
	for (uint p = 0; p < static_cast<uint>(players.size()); p++)
	{
		//Player info
		uint playerID = players.at(p);
		GameObject* currentPlayer = m_gameobjects.at(playerID).get();
		PlayerObject* playerObj = dynamic_cast<PlayerObject*>(currentPlayer);

		for (uint f = 0; f < static_cast<uint>(allfood.size()); f++)
		{
			uint foodID = allfood.at(f);
			GameObject* currentFood = m_gameobjects.at(foodID).get();

			if (playerObj->IsColliding(*currentFood))
			{
				FoodObject* food = dynamic_cast<FoodObject*>(currentFood);
				
				//Remove the food
				removeObjs.push_back(foodID);
				//Add points to player
				playerObj->SetPoints(food->GetWorth());
			}
		}

		for (uint e = 0; e < static_cast<uint>(enemies.size()); e++)
		{
			uint enemyID = enemies.at(e);
			GameObject* currentEnemy = m_gameobjects.at(enemyID).get();

			if (playerObj->IsColliding(*currentEnemy))
			{
				playerObj->SetPoints(-playerObj->GetMaxPoints());
			}
		}
	}

	//Check winconditions for players
	for (uint p = 0; p < static_cast<uint>(players.size()); p++)
	{
		uint playerID = players.at(p);
		GameObject* currentPlayer = m_gameobjects.at(playerID).get();
		PlayerObject* playerObj = dynamic_cast<PlayerObject*>(currentPlayer);

		if (playerObj->CheckWinCondition())
			WINDOW.setTitle("Player: " + std::to_string(playerID) + " won the game!");
	}

	//Clean up objects
	for (uint i = 0; i < static_cast<uint>(removeObjs.size()); i++)
	{
		uint removeID = removeObjs.at(i);
		m_gameobjects.erase(m_gameobjects.begin() + removeID);
	}
}

void Game::Render()
{
	WINDOW.clear();

	for (const auto& obj : m_gameobjects)
		obj->Render();

	WINDOW.setView(SFMLTon::GetCamera());
	WINDOW.display();
}
