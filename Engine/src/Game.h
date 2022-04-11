#pragma once
#include "GameObject.h"

class Game
{
private:
	std::vector<std::unique_ptr<GameObject>> m_gameobjects;


public:
	Game();
	~Game() = default;
	
	//Get all objects with tag
	std::vector<GameObject> GetObjectsWithTag(ETagType tag);

	//Update and render all the objects
	void Update(const float& dt);
	void Render();

};