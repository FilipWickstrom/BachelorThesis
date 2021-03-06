#pragma once
#include "GameObject.h"

#ifdef OOD

class EnemyObject : public RenderObject
{
private:

	int damage = 1;
	vec2 m_velo = {rand() % 32 - 16.f, rand() % 32 - 16.f};

public:

	EnemyObject();

	// Inherited via RenderObject
	virtual void Move(const float& dt) override;
};

#endif