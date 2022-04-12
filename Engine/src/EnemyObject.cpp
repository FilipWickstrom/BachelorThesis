#include "PCH.h"
#include "EnemyObject.h"

EnemyObject::EnemyObject()
	:GameObject(ETagType::enemy)
{
	m_movementSpeed = 50;
	m_velocity = { static_cast<float>(rand() % 3 - 1), static_cast<float>(rand() % 3 - 1)};
	
	m_shape = std::make_unique<sf::CircleShape>(10.f);
	m_shape->setOrigin(m_shape->getLocalBounds().width / 2.f, m_shape->getLocalBounds().height / 2.f);
	m_shape->setFillColor(sf::Color::Magenta);
	m_shape->setPosition({ rand() % WIN_WIDTH * 2.f - WIN_WIDTH, rand() % WIN_HEIGHT * 2.f - WIN_HEIGHT });
}

void EnemyObject::Update(const float& dt)
{
	//Shape does not exist
	if (!m_shape) return;

	vec2 movement = { m_velocity.x * m_movementSpeed * dt,
					  m_velocity.y * m_movementSpeed * dt };

	m_shape->move(movement);
}

void EnemyObject::Render()
{
	WINDOW.draw(*m_shape);
}
