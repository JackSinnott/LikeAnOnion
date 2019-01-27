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
		else if(object == "Blueprint")
		{
			HouseBlueprint bluprint(m_sceneryObjects);
			file >> coord.x >> coord.y >> layer;
			bluprint.initilaize(coord, static_cast<Layers>(layer));
			m_blueprints.push_back(bluprint);
		}
	}

}

Scenery::~Scenery()
{
}

void Scenery::update(sf::Time t_deltaTime)
{
	int i = 0;
	for (HouseBlueprint & blueprint : m_blueprints)
	{
		if (blueprint.inInventory == true)
		{
			blueprint.setPosition(sf::Vector2f(1100 - i * 80, 2000));
			i++;
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

	for (Rock & rock : m_rocks)
	{
		if (rock.getLayer() == t_currentLayer)
		{
			rock.render(t_window);
		}
	}

	for (HouseBlueprint & blueprint : m_blueprints)
	{
		if (blueprint.getLayer() == t_currentLayer)
		{
			blueprint.render(t_window);
		}
	}
}

bool Scenery::checkCollisions(sf::Sprite * t_player, Layers t_playerLayer, int t_type)
{
	bool collide{ false };

	// Player Tree collisions
	if (t_type == 1)
	{
		for (Tree & tree : m_trees)
		{
			if (t_playerLayer == tree.getLayer())
			{
				if (collision::isCollided(*t_player, *tree.getSpriteTrunk()))
				{
					collide = true;
					break;
				}
				else if (collision::isCollided(*t_player, *tree.getSpriteLeaves()))
				{
					collide = true;
					break;
				}
				else
				{
					collide = false;
				}
			}
		}
	}  // Player - Rock Collisions
	else if (t_type == 2)
	{
		for (Rock & rock : m_rocks)
		{
			if (t_playerLayer == rock.getLayer())
			{
				if (collision::isCollided(*t_player, *rock.getBody()))
				{
					collide = true;
					break;
				}
				else
				{
					collide = false;
				}
			}
		}
	}

	else if (t_type == 3)
	{
		for (HouseBlueprint & blueprint : m_blueprints)
		{
			if (t_playerLayer == blueprint.getLayer())
			{
				if (collision::isCollided(*t_player, *blueprint.getBody()))
				{
					collide = true;
					blueprint.inInventory = true;
					break;
				}
				else
				{
					collide = false;
				}
			}
		}
	}

	return collide;
}
