#pragma once
#include "GameObject.h"

class EnemyObject : public GameObject
{
private:
	uint    m_points;
	uint	m_maxPoints;
	float	m_movementSpeed;
	vec2	m_velocity;

public:
	EnemyObject();
	~EnemyObject() = default;

	// Inherited via GameObject
	virtual void Update(const float& dt) override;
	virtual void Render() override;

};