#pragma once
#include "System.hpp"
#include "Coordinator.hpp"
#include "Components.h"
#include "ECS.h"

class Game
{
private:

	Coordinator m_coordinator;
	Entity m_playerEntity;
	std::vector<Entity> m_entities;
	ECS m_ecs;

public:

	Game();
	~Game();
	void Init();
	void Update(const float& dt);
	void Draw();
};