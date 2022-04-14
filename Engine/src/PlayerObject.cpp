#include "PCH.h"
#include "PlayerObject.h"

PlayerObject::PlayerObject()
{
	sf::CircleShape shape(10.0f);
	shape.setFillColor(sf::Color::Blue);

	this->SetShape(shape);
}

void PlayerObject::Move(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_position.y -= m_speed * dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_position.y += m_speed * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_position.x -= m_speed * dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_position.x += m_speed * dt;
	}

	this->SetPosition(m_position);
}

void PlayerObject::AddPoints(const int& score)
{
	m_score += score;
}

void PlayerObject::RemovePoints(const int& score)
{
	m_score -= score;

	if (m_score < 0)
		m_score = 0;
}

const int& PlayerObject::GetPoints() const
{
	return m_score;
}

void PlayerObject::UpdateScale()
{
	m_scale.x = m_score;
	m_scale.y = m_score;

	this->SetScale(m_scale);
}
