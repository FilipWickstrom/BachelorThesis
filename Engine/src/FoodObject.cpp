#include "PCH.h"
#include "FoodObject.h"

#ifdef OOD

FoodObject::FoodObject()
{
	this->SetTag(Tags::GOOD);
	
	sf::CircleShape shape(10.0f);
	shape.setFillColor(sf::Color::Green);

	this->SetShape(shape);

	float x = rand() % 5000 - 2500;
	float y = rand() % 5000 - 2500;

	this->SetPosition({x, y});
}

void FoodObject::Move(const float& dt)
{
	// Doesn't move.
}

#endif