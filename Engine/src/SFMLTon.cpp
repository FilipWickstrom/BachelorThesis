#include "PCH.h"
#include "SFMLTon.h"

SFMLTon::SFMLTon()
{
	m_window.create(sf::VideoMode(1600, 900), "SFML works!");
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
