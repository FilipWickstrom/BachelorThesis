#include "PCH.h"
#include "SFMLTon.h"

SFMLTon::SFMLTon()
{
#if DRAW_GAME
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Points: 0");
#else
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test environment");
#endif

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
