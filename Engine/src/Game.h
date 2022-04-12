#pragma once
#include "System.h"
#include "Coordinator.h"

class Game
{
private:

	Coordinator m_coordinator;
	Entity m_playerEntity;
	std::vector<Entity> m_entities;
	std::shared_ptr<RenderSystem> m_renderSystem;
	std::shared_ptr<MovementSystem> m_movementSystem;
	std::shared_ptr<CollisionSystem> m_collisionSystem;

	sf::Font m_font;
	sf::Text m_scoreText;

public:

	Game();
	~Game();
	void Init();
	void Update(const float& dt);
	void Draw();
};