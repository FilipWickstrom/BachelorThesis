#pragma once
#include "GameObject.h"

class FoodObject : public GameObject
{
private:
	int m_worth;

public:
	FoodObject();
	~FoodObject() = default;

	const int& GetWorth() const;

	// Inherited via GameObject
	virtual void Update(const float& dt) override;
	virtual void Render() override;

};