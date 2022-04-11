#include "PCH.h"
#include "SFMLTon.h"

SFMLTon::SFMLTon()
{
	m_window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Thesis: OOD vs DOD vs DOD-MT");
	m_camera.setCenter(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f);
	m_camera.setSize(WIN_WIDTH, WIN_HEIGHT);
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

sf::View& SFMLTon::GetCamera()
{
	return Get().m_camera;
}
