#include "PCH.h"
#include "GameDOD.h"
#include "Components.h"



GameDOD::GameDOD()
{
	//Create a player
	m_playerEnt = m_registry.create();
	m_registry.emplace<comp::Tag>(m_playerEnt, ETagType::player);
	const auto& poscomp = m_registry.emplace<comp::Transform>(m_playerEnt, vec2(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f));
	m_registry.emplace<comp::Score>(m_playerEnt, 0, GOALPOINTS);
	m_registry.emplace<comp::CircleShape>(m_playerEnt, 10.f, sf::Color::Blue, poscomp.position);
	m_registry.emplace<comp::Collider>(m_playerEnt, 10.f);


	//Create enemies
	for (uint i = 0; i < NR_OF_ENEMIES; i++)
	{
		entt::entity enemyEnt = m_registry.create();
		m_registry.emplace<comp::Tag>(enemyEnt, ETagType::enemy);

		vec2 position = { (rand() % WIN_WIDTH	* SPAWNDENSITY - WIN_WIDTH)		+ WIN_WIDTH,
						  (rand() % WIN_HEIGHT	* SPAWNDENSITY - WIN_HEIGHT)	+ WIN_HEIGHT };
		vec2 velocity = { static_cast<float>(rand() % 3 - 1) * 50.f,
						  static_cast<float>(rand() % 3 - 1) * 50.f };
		
		m_registry.emplace<comp::Transform>(enemyEnt, position, velocity);
		m_registry.emplace<comp::CircleShape>(enemyEnt, 10.f, sf::Color::Magenta, position);
		m_registry.emplace<comp::Collider>(enemyEnt, 10.f);
	}


	//Create food
	for (uint i = 0; i < NR_OF_FOOD; i++)
	{
		int worth		= rand() % 11 + 5;
		ETagType tag	= rand() % 2 == 0 ? ETagType::goodfood : ETagType::badfood;
		vec2 position	= { (rand() % WIN_WIDTH		* SPAWNDENSITY - WIN_WIDTH)		+ WIN_WIDTH,
							(rand() % WIN_HEIGHT	* SPAWNDENSITY - WIN_HEIGHT)	+ WIN_HEIGHT };
		sf::Color color = sf::Color::Green;

		if (tag == ETagType::badfood)
		{
			worth *= -1;
			color = sf::Color::Red;
		}

		entt::entity foodEnt = m_registry.create();
		m_registry.emplace<comp::Transform>(foodEnt, position);
		m_registry.emplace<comp::Worth>(foodEnt, worth);
		m_registry.emplace<comp::Tag>(foodEnt, tag);
		m_registry.emplace<comp::CircleShape>(foodEnt, static_cast<float>(worth), color, position);
		m_registry.emplace<comp::Collider>(foodEnt, static_cast<float>(worth));
	}

	m_gameOver = false;
}

bool GameDOD::CheckCollision(const vec2& pos1, const vec2& pos2, const float& rad1, const float& rad2)
{
	float xdist = pos2.x - pos1.x;
	float ydist = pos2.y - pos1.y;
	float distance = std::sqrt(xdist * xdist + ydist * ydist);

	if (distance < rad1 + rad2)
		return true;

	return false;
}

void GameDOD::Update(const float& dt)
{
	if (m_gameOver) return;

	auto& playerTrans		= m_registry.get<comp::Transform>(m_playerEnt);
	auto& playerShape		= m_registry.get<comp::CircleShape>(m_playerEnt);
	auto& playerScore		= m_registry.get<comp::Score>(m_playerEnt);
	auto& playerCollider	= m_registry.get<comp::Collider>(m_playerEnt);

	/*
		Update player movement
	*/
	//Get input from the player controller
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		playerTrans.velocity.x += -PLAYERSPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		playerTrans.velocity.x += PLAYERSPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		playerTrans.velocity.y += -PLAYERSPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		playerTrans.velocity.y += PLAYERSPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		playerTrans.velocity.x *= 2;
		playerTrans.velocity.y *= 2;
	}

	playerTrans.position += { playerTrans.velocity.x * dt,
							  playerTrans.velocity.y * dt };
	playerTrans.velocity = { 0.f, 0.f };
	playerShape.shape.setPosition(playerTrans.position);
	SFMLTon::GetCamera().setCenter(playerTrans.position);


	/*
		Update every other entities position and check collision with player
	*/
	//Avoids the player by execluding score
	const auto& view = m_registry.view<comp::CircleShape, comp::Transform, comp::Tag, comp::Collider>(entt::exclude<comp::Score>);
	for (const auto& entity : view)
	{
		auto& entPos		= m_registry.get<comp::Transform>(entity);
		auto& entShape		= m_registry.get<comp::CircleShape>(entity);
		auto& entTag		= m_registry.get<comp::Tag>(entity);
		auto& entCollider	= m_registry.get<comp::Collider>(entity);

		//Move the entity
		entPos.position += { entPos.velocity.x * dt,
							 entPos.velocity.y * dt };
		entShape.shape.setPosition(entPos.position);


		//Check collision
		//if (playerShape.shape.getGlobalBounds().intersects(entShape.shape.getGlobalBounds()))					//Expensive
		if (CheckCollision(playerTrans.position, entPos.position, playerCollider.radius, entCollider.radius))	//Cheaper
		{
			switch (entTag.type)
			{
			case ETagType::enemy:
			{
				playerScore.current = 0;
				WINDOW.setTitle("Points: " + std::to_string(playerScore.current));
				playerShape.shape.setRadius(playerScore.current + 10.f);
				playerCollider.radius = playerScore.current + 10.f;
				playerShape.shape.setOrigin(playerShape.shape.getLocalBounds().width / 2.f,
											playerShape.shape.getLocalBounds().height / 2.f);
				break;
			}
			case ETagType::goodfood:
			case ETagType::badfood:
			{
				auto worth = m_registry.try_get<comp::Worth>(entity);
				if (!worth) return;

				playerScore.current += worth->points;
				if (playerScore.current < 0) 
				{
					playerScore.current = 0;
				}
				else
				{
					if (playerScore.current >= playerScore.max)
					{
						WINDOW.setTitle("You win the game!");
						m_gameOver = true;
						return;
					}
				}
				m_registry.remove<comp::CircleShape>(entity);


				WINDOW.setTitle("Points: " + std::to_string(playerScore.current));
				playerShape.shape.setRadius(playerScore.current + 10.f);
				playerCollider.radius = playerScore.current + 10.f;
				playerShape.shape.setOrigin(playerShape.shape.getLocalBounds().width / 2.f,
											playerShape.shape.getLocalBounds().height / 2.f);

				break;
			}
			default:
				break;
			}
		}
	}
}

void GameDOD::Render()
{
	WINDOW.clear();

	const auto& view = m_registry.view<comp::CircleShape>();
	for (const auto& entity : view)
	{
		const auto& circleshape = m_registry.get<comp::CircleShape>(entity);
		WINDOW.draw(circleshape.shape);
	}

	WINDOW.setView(SFMLTon::GetCamera());
	WINDOW.display();
}