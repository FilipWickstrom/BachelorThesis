#pragma once
#include "Components.h"

class ECS
{
private:

	ECS();
	~ECS() = default;
	static std::queue<Entity> m_availableEntities;
	static std::vector<Entity> m_activeEntities;

public:

	static auto& Get()
	{
		static ECS instance;
		return instance;
	}

	static std::array<Transform, MAX_ENTITIES> m_transforms;
	static std::array<Renderable, MAX_ENTITIES> m_renderables;
	static std::array<Tag, MAX_ENTITIES> m_tags;
	static std::array<Value, MAX_ENTITIES> m_values;

	static Entity CreateEntity();
	void DestroyEntity(const Entity& entity);

	static std::vector<Entity>& GetActiveEntities();
};