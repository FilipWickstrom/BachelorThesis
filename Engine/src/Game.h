#pragma once
#include "System.hpp"
#include "Coordinator.hpp"
#include "Components.h"

class Game
{
private:

	Coordinator m_coordinator;
	Entity m_playerEntity;
	std::vector<Entity> m_entities;

	std::array<Transform, MAX_ENTITIES> m_transforms;

public:

	Game();
	~Game();
	void Init();
	void Update(const float& dt);
	void Draw();
};