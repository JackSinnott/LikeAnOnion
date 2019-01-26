#include "Scenery.h"

Scenery::Scenery(int t_numOfTrees)
{
	std::srand(static_cast<unsigned int>(time(NULL)));

	if (!m_sceneryObjects.loadFromFile("cow.jpg"))
	{
		std::cout << "Oh no" << std::endl;
	}

	for (int i = 0; i < t_numOfTrees; i++)
	{
		Tree tree(m_sceneryObjects);
		m_trees.push_back(tree);
	}

	initialize();
}

Scenery::~Scenery()
{
}

void Scenery::update(sf::Time t_deltaTime)
{
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

void Scenery::initialize()
{
	for (Tree & tree : m_trees)
	{
		tree.initilaize(sf::Vector2f(rand() % 200, rand() % 200),static_cast<Layers>(rand() % 3));
	}
}
