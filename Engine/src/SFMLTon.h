#pragma once

class SFMLTon
{
private:

	sf::RenderWindow m_window;
	SFMLTon();
	static auto& Get();

public:

	static sf::RenderWindow& GetWindow();
};