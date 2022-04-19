#include "PCH.h"
#include "PlayerObject.h"

PlayerObject::PlayerObject()
	:GameObject(ETagType::player)
{
	m_defaultSize = 10;
	m_points = 0;
	m_maxPoints = GOALPOINTS;
	m_movementSpeed = PLAYERSPEED;
	m_shape = std::make_unique<sf::CircleShape>(static_cast<float>(m_defaultSize));
	m_shape->setOrigin(m_shape->getLocalBounds().width / 2.f, m_shape->getLocalBounds().height / 2.f);
	m_shape->setFillColor(sf::Color::Blue);
	SetCollisionRadius(static_cast<float>(m_defaultSize));
}

void PlayerObject::AddPoints(const int& points)
{
	m_points += points;
	if (m_points < 0)
		m_points = 0;

	sf::CircleShape* circleShape = dynamic_cast<sf::CircleShape*>(m_shape.get());
	circleShape->setRadius(static_cast<float>(m_defaultSize + m_points));
	SetCollisionRadius(static_cast<float>(m_defaultSize + m_points));
	m_shape->setOrigin(m_shape->getLocalBounds().width / 2.f, m_shape->getLocalBounds().height / 2.f);
	WINDOW.setTitle("Points: " + std::to_string(m_points));
}

void PlayerObject::ResetPoints()
{
	m_points = 0;
	sf::CircleShape* circleShape = dynamic_cast<sf::CircleShape*>(m_shape.get());
	circleShape->setRadius(static_cast<float>(m_defaultSize));
	SetCollisionRadius(static_cast<float>(m_defaultSize));
	m_shape->setOrigin(m_shape->getLocalBounds().width / 2.f, m_shape->getLocalBounds().height / 2.f);
	WINDOW.setTitle("Points: " + std::to_string(m_points));
}

bool PlayerObject::CheckWinCondition()
{
	return m_points >= m_maxPoints ? true : false;
}

void PlayerObject::Update(const float& dt)
{
	//Shape does not exist
	if (!m_shape) return;

	vec2 velocity = { 0.f, 0.f };

	//Get input from the player controller
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x += -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y += -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.x *= 2;
		velocity.y *= 2;
	}
	
	vec2 movement = { velocity.x * m_movementSpeed * dt,
					  velocity.y * m_movementSpeed * dt };

	//Move player and camera
	m_shape->move(movement);
	SFMLTon::GetCamera().move(movement);
}

void PlayerObject::Render()
{
	WINDOW.draw(*m_shape);
}

