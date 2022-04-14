#include "PCH.h"
#include "EnemyObject.h"

EnemyObject::EnemyObject()
{
	this->SetTag(Tags::BAD);

	sf::CircleShape shape(10.0f);
	shape.setFillColor(sf::Color::Red);
	this->SetShape(shape);

	float x = rand() % 5000 - 2500;
	float y = rand() % 5000 - 2500;

	this->SetPosition({ x, y });
}

void EnemyObject::Move(const float& dt)
{
	m_position.x += m_velo.x * dt;
	m_position.y += m_velo.y * dt;

	this->SetPosition(m_position);
}
