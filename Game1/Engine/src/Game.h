#pragma once
#ifdef DOD
#include "Components.h"
#include "ECS.h"
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
	bool IsColliding(const vec2& pos1, const vec2& pos2,
					 const float& rad1, const float& rad2);
};
#endif

#ifdef OOD
#include "FoodObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
class Game
{
private:

	PlayerObject* m_player;
	std::vector<RenderObject*> m_objects;

public:

	Game();
	~Game();

	void Init();
	void Update(const float& dt);
	void Draw();
};
#endif