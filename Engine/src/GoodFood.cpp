#include "PCH.h"
#include "GoodFood.h"

GoodFood::GoodFood()
	:GameObject(ETagType::goodfood)
{
	m_shape = std::make_unique<sf::CircleShape>(10.f);
	m_shape->setOrigin(m_shape->getLocalBounds().width / 2.f, m_shape->getLocalBounds().height / 2.f);
	m_shape->setFillColor(sf::Color::Green);
	m_shape->setPosition({ rand() % WIN_WIDTH * 2.f - WIN_WIDTH, rand() % WIN_HEIGHT * 2.f - WIN_HEIGHT });
}

void GoodFood::Update(const float& dt)
{
	//Does nothing
}

void GoodFood::Render()
{
	WINDOW.draw(*m_shape);
}
