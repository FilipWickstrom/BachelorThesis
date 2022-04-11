#pragma once
#include "System.h"

class Game
{
private:

	std::vector<Entity> m_entities;
	std::shared_ptr<RenderSystem> m_renderSystem;
	std::shared_ptr<MovementSystem> m_movementSystem;

public:

	Game();
	void Init();
	void Update(const float& dt);
	void Draw();
};