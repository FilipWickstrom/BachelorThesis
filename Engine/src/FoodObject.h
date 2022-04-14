#pragma once
#include "GameObject.h"

class FoodObject : public RenderObject
{
private:

	int m_worth = 1;

public:

	FoodObject();

	// Inherited via RenderObject
	virtual void Move(const float& dt) override;
};
