#pragma once

class GameDOD
{
private:
	entt::registry m_registry;
	entt::entity   m_playerEnt;
	bool		   m_gameOver;

private: 
	void PlayerInputSystem(const float& dt);
	void EnemyMoveSystem(const float& dt);
	void CollisionSystem();
	void UpdateShapeSystem();
	bool GoalSystem();

public:
	GameDOD();
	~GameDOD() = default;

	//Update and render all the entities
	void Update(const float& dt);
	void Render();

};