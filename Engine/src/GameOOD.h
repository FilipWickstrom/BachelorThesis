#pragma once
#include "GameObject.h"

class GameOOD
{
private:
	std::vector<std::unique_ptr<GameObject>> m_gameobjects;
	uint									 m_playerID;
	bool									 m_gameOver;

public:
	GameOOD();
	~GameOOD() = default;
	
	//Update and render all the objects
	void Update(const float& dt);
	void Render();

};