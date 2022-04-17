#include "PCH.h"
#include "GameDOD.h"
#include "Components.h"


GameDOD::GameDOD()
{
	//Create a player
	m_playerEnt = m_registry.create();
	m_registry.emplace<comp::Tag>(m_playerEnt, ETagType::player);
	m_registry.emplace<comp::Position>(m_playerEnt, vec2(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f));
	m_registry.emplace<comp::Velocity>(m_playerEnt, PLAYERSPEED);
	m_registry.emplace<comp::Score>(m_playerEnt, 0, GOALPOINTS);
	m_registry.emplace<comp::CircleShape>(m_playerEnt, 10.f, sf::Color::Blue);


	//Create enemies
	for (uint i = 0; i < NR_OF_ENEMIES; i++)
	{
		entt::entity enemyEnt = m_registry.create();
		m_registry.emplace<comp::Tag>(enemyEnt, ETagType::enemy);

		vec2 position = { (rand() % WIN_WIDTH	* SPAWNDENSITY - WIN_WIDTH)		+ WIN_WIDTH,
						  (rand() % WIN_HEIGHT	* SPAWNDENSITY - WIN_HEIGHT)	+ WIN_HEIGHT };
		m_registry.emplace<comp::Position>(enemyEnt, position);

		m_registry.emplace<comp::Velocity>(enemyEnt, 50.f, vec2(static_cast<float>(rand() % 3 - 1), 
																static_cast<float>(rand() % 3 - 1)));
		m_registry.emplace<comp::CircleShape>(enemyEnt, 10.f, sf::Color::Magenta);
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
		m_registry.emplace<comp::Position>(foodEnt, position);
		m_registry.emplace<comp::Worth>(foodEnt, worth);
		m_registry.emplace<comp::Tag>(foodEnt, tag);
		m_registry.emplace<comp::CircleShape>(foodEnt, static_cast<float>(worth), color);
	}

	m_gameOver = false;
}

void GameDOD::PlayerInputSystem(const float& dt)
{
	auto& velocity = m_registry.get<comp::Velocity>(m_playerEnt);

	//Get input from the player controller
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.direction.x += -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.direction.x += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.direction.y += -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.direction.y += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.direction.x *= 2;
		velocity.direction.y *= 2;
	}

	vec2 movement = { velocity.direction.x * velocity.speed * dt,
					  velocity.direction.y * velocity.speed * dt };

	auto& poscomp = m_registry.get<comp::Position>(m_playerEnt);
	poscomp.position += movement;
	SFMLTon::GetCamera().move(movement);

	//Reset direction
	velocity.direction = { 0.f, 0.f };
}

void GameDOD::EnemyMoveSystem(const float& dt)
{
	//Excluding player entity by using the score component
	const auto& group = m_registry.view<comp::Position, comp::Velocity>(entt::exclude<comp::Score>);
	for (const auto& entity : group)
	{
		auto& position = m_registry.get<comp::Position>(entity);
		const auto& velocity = m_registry.get<comp::Velocity>(entity);

		vec2 movement = {	velocity.direction.x * velocity.speed * dt,
							velocity.direction.y * velocity.speed * dt };
		position.position += movement;
	}
}

void GameDOD::CollisionSystem()
{
	auto& playershape = m_registry.get<comp::CircleShape>(m_playerEnt);
	auto& playerScore = m_registry.get<comp::Score>(m_playerEnt);

	//Excluding player entity by using the score component
	const auto& group = m_registry.view<comp::CircleShape, comp::Tag>(entt::exclude<comp::Score>);
	for (const auto& entity : group)
	{
		const auto& circleshape = m_registry.get<comp::CircleShape>(entity);
		const auto& tag = m_registry.get<comp::Tag>(entity);

		if (playershape.shape.getGlobalBounds().intersects(circleshape.shape.getGlobalBounds()))
		{
			switch (tag.type)
			{
			case ETagType::enemy:
			{
				playerScore.current = 0;
				break;
			}
			case ETagType::goodfood:
			case ETagType::badfood:
			{
				auto worth = m_registry.try_get<comp::Worth>(entity);
				if (!worth) return;
				
				playerScore.current += worth->points;
				if (playerScore.current < 0) playerScore.current = 0;

				m_registry.remove<comp::CircleShape>(entity);
				break;
			}
			default:
				break;
			}

			WINDOW.setTitle("Points: " + std::to_string(playerScore.current));
			playershape.shape.setRadius(playerScore.current + 10.f);
			playershape.shape.setOrigin(playershape.shape.getLocalBounds().width / 2.f,
										playershape.shape.getLocalBounds().height / 2.f);
		}
	}

}

void GameDOD::UpdateShapeSystem()
{
	const auto& group = m_registry.view<comp::Position, comp::CircleShape>();
	for (const auto& entity : group)
	{
		const auto& poscomp = m_registry.get<comp::Position>(entity);
		auto& circleshape = m_registry.get<comp::CircleShape>(entity);
		circleshape.shape.setPosition(poscomp.position);
	}
}

bool GameDOD::GoalSystem()
{
	const auto& score = m_registry.get<comp::Score>(m_playerEnt);
	if (score.current >= score.max)
	{
		WINDOW.setTitle("You win the game!");
		return false;
	}
	return true;
}

void GameDOD::Update(const float& dt)
{
	if (m_gameOver) return;

	PlayerInputSystem(dt);
	EnemyMoveSystem(dt);
	UpdateShapeSystem();
	CollisionSystem();
	
	if (!GoalSystem()) m_gameOver = true;
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