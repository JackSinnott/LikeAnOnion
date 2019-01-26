#include "Scenery.h"

Scenery::Scenery(int t_numOfTrees)
{
	std::srand(static_cast<unsigned int>(time(NULL)));

	if (!m_sceneryObjects.loadFromFile("ASSETS/TreesSprites.png"))
	{
		std::cout << "Oh no" << std::endl;
	}

	std::ifstream file;
	file.open("Forest.txt");

	std::string object;
	sf::Vector2f coord;
	int layer;

	while(file >> object)
	{
		if (object == "Tree")
		{
			Tree tree(m_sceneryObjects);
			file >> coord.x >> coord.y >> layer;
			tree.initilaize(coord, static_cast<Layers>(layer));
			m_trees.push_back(tree);
		}
		else if (object == "Rock")
		{
			Rock rock(m_sceneryObjects);
			file >> coord.x >> coord.y >> layer;
			rock.initilaize(coord, static_cast<Layers>(layer));
			m_rocks.push_back(rock);
		}
	}

}

Scenery::~Scenery()
{
}

void Scenery::update(sf::Time t_deltaTime, sf::Sprite * t_player, Layers t_playerLayer)
{
	// Player Tree collisions
	for (Tree & tree : m_trees)
	{
		if (t_playerLayer == tree.getLayer())
		{
			if (collision::isCollided(*t_player, *tree.getBody()))
			{
				std::cout << "Collide" << std::endl;
			}
			else
			{
				std::cout << "Nah" << std::endl;
			}
		}
	}
}

void Scenery::render(sf::RenderWindow &t_window, Layers t_currentLayer)
{
	for (Tree & tree : m_trees)
	{
		if (tree.getLayer() == t_currentLayer)
		{
			tree.render(t_window);
		}
	}
}
