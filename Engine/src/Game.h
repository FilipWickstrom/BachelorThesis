#pragma once
#include "GameObject.h"

class Game
{
private:
	std::vector<std::unique_ptr<GameObject>> m_gameobjects;

private:


public:
	Game();
	~Game() = default;
	
	//Gets a vector of all the tagged objects by id
	//[Optimize] by sending in a number of tags to avoid searching multiple times
	void GetObjectsWithTag(ETagType tag, std::vector<uint>& vec);

	//Update and render all the objects
	void Update(const float& dt);
	void Render();

};