#pragma once

class GameDOD
{
private:
	entt::registry m_registry;
	entt::entity   m_playerEnt;
	bool		   m_gameOver;

public:
	GameDOD();
	~GameDOD() = default;

	//Update and render all the entities
	void Update(const float& dt);
	void Render();

};