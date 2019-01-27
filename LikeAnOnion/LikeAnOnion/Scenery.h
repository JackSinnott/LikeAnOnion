#pragma once
#include "MyVector3.h"
#include "Layer.h"
#include "Tree.h"
#include "Rock.h"
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

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window, Layers t_currentLayer);
	bool checkCollisions(sf::Sprite * t_player, Layers t_playerLayer, int t_type);

private:

	std::vector<Tree> m_trees;
	std::vector<Rock> m_rocks;

	sf::Texture m_sceneryObjects;

};

