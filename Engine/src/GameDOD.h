#pragma once

class GameDOD
{
private:
	entt::registry m_registry;
	entt::entity   m_playerEnt;
	bool		   m_gameOver;

private:
	bool CheckCollision(const vec2& pos1, const vec2& pos2, 
						const float& rad1, const float& rad2);

public:
	GameDOD();
	~GameDOD() = default;

	//Update and render all the entities
	void Update(const float& dt);
	void Render();

};