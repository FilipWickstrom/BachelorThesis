#pragma once
#include "GameObject.h"

class PlayerObject : public GameObject
{
private:
	Health m_health;
	float  m_movementSpeed;

public:
	PlayerObject();
	~PlayerObject() = default;

	
	// Inherited via GameObject
	virtual void Update(const float& dt);
	virtual void Render() override;

};