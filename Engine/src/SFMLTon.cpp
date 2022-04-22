#include "PCH.h"
#include "SFMLTon.h"

SFMLTon::SFMLTon()
{
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test environment");
	m_view.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
}

auto& SFMLTon::Get()
{
	static SFMLTon instance;
	return instance;
}

sf::RenderWindow& SFMLTon::GetWindow()
{
	return Get().m_window;
}

sf::View& SFMLTon::GetView()
{
	return Get().m_view;
}
