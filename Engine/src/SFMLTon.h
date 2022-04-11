#pragma once

class SFMLTon
{
private:
	sf::RenderWindow m_window;
	sf::View m_camera;

	SFMLTon();
	static auto& Get();

public:

	static sf::RenderWindow& GetWindow();
	static sf::View& GetCamera();
};