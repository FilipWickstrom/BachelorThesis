#include "PCH.h"
#include "PlayerObject.h"

PlayerObject::PlayerObject()
	:GameObject(ETagType::player)
{
	m_movementSpeed = 100;
	m_shape = std::make_unique<sf::RectangleShape>(vec2(20, 20));
	m_shape->setOrigin(m_shape->getLocalBounds().width / 2.f, m_shape->getLocalBounds().height / 2.f);
	m_shape->setFillColor(sf::Color::Blue);
	m_shape->setOutlineColor(sf::Color::White);
}

void PlayerObject::Update(const float& dt)
{
	//Shape does not exist
	if (!m_shape) return;

	vec2 velocity = { 0.f, 0.f };

	//Get input from the player controller
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y = 1;
	
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
