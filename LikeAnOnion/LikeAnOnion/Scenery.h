#pragma once
#include "MyVector3.h"
#include "Layer.h"
#include "Tree.h"
#include <time.h>

class Scenery
{
public:
	Scenery(int t_numOfTrees);
	~Scenery();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window, Layers t_currentLayer);

private:
	
	void initialize();

	std::vector<Tree> m_trees;

	sf::Texture m_sceneryObjects;

};

