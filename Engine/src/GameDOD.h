#pragma once

class GameDOD
{
private:
	entt::registry m_registry;

public:
	GameDOD();
	~GameDOD() = default;

	//Update and render all the objects
	void Update(const float& dt);
	void Render();

};