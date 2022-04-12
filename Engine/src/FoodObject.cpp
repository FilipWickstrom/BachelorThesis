#include "PCH.h"
#include "FoodObject.h"

FoodObject::FoodObject()
	:GameObject()
{
	m_worth = rand() % 11 + 5;
	m_shape = std::make_unique<sf::CircleShape>(static_cast<float>(m_worth));

	// Randomize to be good or bad
	int posOrNeg = rand() % 2;	//0 or 1
	if (posOrNeg == 0)
	{
		this->m_tag = ETagType::badfood;
		m_worth *= -1;
		m_shape->setFillColor(sf::Color::Red);
	}
	else
	{
		this->m_tag = ETagType::goodfood;
		m_shape->setFillColor(sf::Color::Green);
	}

	m_shape->setOrigin(m_shape->getLocalBounds().width / 2.f, m_shape->getLocalBounds().height / 2.f);
	m_shape->setPosition({ rand() % WIN_WIDTH * 2.f - WIN_WIDTH, rand() % WIN_HEIGHT * 2.f - WIN_HEIGHT });
}

const int& FoodObject::GetWorth() const
{
	return m_worth;
}

void FoodObject::Update(const float& dt)
{
	//Does nothing
}

void FoodObject::Render()
{
	WINDOW.draw(*m_shape);
}
