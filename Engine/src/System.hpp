#pragma once

class Coordinator;

#include <set>


class System
{
public:
	std::set<Entity> m_entities;
};

class RenderSystem : public System
{
public:
	void Render(Coordinator& coord);
};

class MovementSystem : public System
{
public:
	void Update(Coordinator& coord, const float& dt);
};

class CollisionSystem : public System
{
private:

	struct CollInfo
	{
		Entity player;
		Entity other;
	};

	std::vector<CollInfo> m_collisions;

public:
	void Detect(const Entity& playerEntity, Coordinator& coord);
	void Act(Coordinator& coord);
};

