#pragma once
#include "MyVector3.h"
#include "Layer.h"
class HouseBlueprint
{
public:
	HouseBlueprint(sf::Texture &t_sceneryTexture);
	~HouseBlueprint();

	void initilaize(MyVector3 t_position, Layers t_layer);
	void render(sf::RenderWindow &t_window);
	void setPosition(sf::Vector2f pos);
	sf::Sprite* getBody();
	Layers getLayer();

	bool inInventory{ false };

private:

	MyVector3 m_position;

	sf::Sprite m_sprite;

	Layers m_layer;
};

