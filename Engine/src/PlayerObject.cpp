#include "PCH.h"
#include "PlayerObject.h"

PlayerObject::PlayerObject()
	:GameObject(ETagType::player)
{
	m_defaultSize = 10;
	m_points = 0;
	m_maxPoints = GOALPOINTS;
	m_shape = sf::CircleShape(static_cast<float>(m_defaultSize));
	m_shape.setOrigin(m_shape.getLocalBounds().width / 2.f, m_shape.getLocalBounds().height / 2.f);
	m_shape.setFillColor(sf::Color::Blue);
	SetCollisionRadius(static_cast<float>(m_defaultSize));
}

void PlayerObject::AddPoints(const int& points)
{
	m_points += points;
	if (m_points < 0)
		m_points = 0;

	m_shape.setRadius(static_cast<float>(m_defaultSize + m_points));
	SetCollisionRadius(static_cast<float>(m_defaultSize + m_points));
	m_shape.setOrigin(m_shape.getLocalBounds().width / 2.f, m_shape.getLocalBounds().height / 2.f);
#if DRAW_GAME
	WINDOW.setTitle("Points: " + std::to_string(m_points));
#endif
}

void PlayerObject::ResetPoints()
{
	m_points = 0;
	m_shape.setRadius(static_cast<float>(m_defaultSize));
	SetCollisionRadius(static_cast<float>(m_defaultSize));
	m_shape.setOrigin(m_shape.getLocalBounds().width / 2.f, m_shape.getLocalBounds().height / 2.f);
#if DRAW_GAME
	WINDOW.setTitle("Points: " + std::to_string(m_points));
#endif
}

bool PlayerObject::CheckWinCondition()
{
	return m_points >= m_maxPoints ? true : false;
}

void PlayerObject::Update(const float& dt)
{
	vec2 velocity = { 0.f, 0.f };

	//Get input from the player controller
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x += -PLAYERSPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += PLAYERSPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y += -PLAYERSPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y += PLAYERSPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.x *= 2;
		velocity.y *= 2;
	}
	
	vec2 movement = { velocity.x * dt,
					  velocity.y * dt };

	//Move player and camera
	m_shape.move(movement);
	SFMLTon::GetCamera().move(movement);
}

void PlayerObject::Render()
{
	WINDOW.draw(m_shape);
}

