#pragma once
#include "Components.h"

class ECS
{
private:

	std::queue<Entity> m_availableEntities;
	std::vector<Entity> m_activeEntities;

public:
	ECS();
	~ECS() = default;

	std::vector<Transform> transforms;
	std::vector<Renderable> renderables;
	std::vector<Tag> tags;
	std::vector<Value> values;

	Entity CreateEntity();
	void DestroyEntity(const Entity& entity);

	std::vector<Entity>& GetActiveEntities();
};