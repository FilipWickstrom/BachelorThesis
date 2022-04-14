#pragma once
#include "GameObject.h"

#ifdef OOD

class PlayerObject : public RenderObject
{
private:

	int m_score = 1;
	float m_speed = 125.0f;

public:

	PlayerObject();

	// Inherited via RenderObject
	virtual void Move(const float& dt) override;

	void AddPoints(const int& score);
	void RemovePoints(const int& score);
	const int& GetPoints() const;
	void UpdateScale();
};

#endif