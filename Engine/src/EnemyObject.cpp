#include "PCH.h"
#include "EnemyObject.h"

EnemyObject::EnemyObject()
	:GameObject(ETagType::enemy)
{
	m_movementSpeed = 50.f;
	m_velocity = { static_cast<float>(rand() % 3 - 1), static_cast<float>(rand() % 3 - 1)};
	
	m_shape = std::make_unique<sf::CircleShape>(10.f);
	m_shape->setOrigin(m_shape->getLocalBounds().width / 2.f, m_shape->getLocalBounds().height / 2.f);
	m_shape->setFillColor(sf::Color::Magenta);

	// Spawn location
	// Max X:	winWidth	* SPAWNDENSITY
	// Min X:  -winWidth	* SPAWNDENSITY
	// Max Y:   winHeight	* SPAWNDENSITY
	// Min Y:  -winHeight   * SPAWNDENSITY
	m_shape->setPosition(
		(rand() % WIN_WIDTH * SPAWNDENSITY	- WIN_WIDTH)	+ WIN_WIDTH,
		(rand() % WIN_HEIGHT * SPAWNDENSITY - WIN_HEIGHT)	+ WIN_HEIGHT
	);
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
