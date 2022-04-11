#pragma once
#include "GameObject.h"

class GoodFood : public GameObject
{
private:
	uint m_worth;

public:
	GoodFood();
	~GoodFood() = default;



	// Inherited via GameObject
	virtual void Update(const float& dt) override;

	virtual void Render() override;

};