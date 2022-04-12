#pragma once
#include "GameObject.h"

class Game
{
private:
	std::vector<std::unique_ptr<GameObject>> m_gameobjects;
	uint									 m_playerID;

public:
	Game();
	~Game() = default;
	
	//Gets a vector of all the tagged objects by id
	//[Can be optimized] by sending in a number of tags to avoid searching multiple times
	void GetObjectsWithTag(const ETagType& tag, std::vector<uint>& vec);

	//Update and render all the objects
	void Update(const float& dt);
	void Render();

};