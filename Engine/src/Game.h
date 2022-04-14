#pragma once
#include "Components.h"
#include "ECS.h"

#ifdef OOD
#include "FoodObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
#endif

#ifdef DOD
class Game
{
private:

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
#endif

#ifdef OOD
class Game
{
private:

	PlayerObject m_player;
	std::vector<RenderObject*> m_objects;

public:

	Game();
	~Game();

	void Init();
	void Update(const float& dt);
	void Draw();

};
#endif