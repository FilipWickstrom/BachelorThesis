#include "PCH.h"
#include "Game.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
#include "GoodFood.h"

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

	//Add 50% good food
	for (uint i = 0; i < (NR_OF_ENEMIES / 2); i++)
	{
		std::unique_ptr<GameObject> goodfood = std::make_unique<GoodFood>();
		m_gameobjects.push_back(std::move(goodfood));
	}

	//Add some bad food - 1/5 of all food is bad

}

void Game::Update(const float& dt)
{
	//Move everything

	//Check collision


	// Only movement for now here in update
	for (auto& obj : m_gameobjects)
	{
		obj->Update(dt);
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
