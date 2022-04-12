#pragma once
#include "GameObject.h"

class PlayerObject : public GameObject
{
private:
	int		m_defaultSize;
	int		m_points;
	int		m_maxPoints;
	float	m_movementSpeed;

public:
	PlayerObject();
	~PlayerObject() = default;

	void SetPoints(const int& points);
	bool CheckWinCondition();
	
	// Inherited via GameObject
	virtual void Update(const float& dt);
	virtual void Render() override;

};