#pragma once
#include "MyVector3.h"
#include "Layer.h"

class Tree
{
public:
	
	Tree(sf::Texture &t_sceneryTexture);
	~Tree();
	
	void initilaize(MyVector3 t_position, Layers t_layer);
	void render(sf::RenderWindow &t_window);
	sf::Sprite* getBody();
	Layers getLayer();
private:

	MyVector3 m_position;

	sf::Sprite m_sprite;

	Layers m_layer;
};

