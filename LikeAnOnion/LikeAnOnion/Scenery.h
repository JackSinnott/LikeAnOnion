#pragma once
#include "MyVector3.h"
#include "Layer.h"
#include "Tree.h"
#include <time.h>
#include "collision.h"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <string>

class Scenery
{
public:
	Scenery(int t_numOfTrees);
	~Scenery();

	void update(sf::Time t_deltaTime, sf::Sprite * t_player, Layers t_playerLayer);
	void render(sf::RenderWindow &t_window, Layers t_currentLayer);

private:
	
	void initialize();

	std::vector<Tree> m_trees;

	sf::Texture m_sceneryObjects;

};

