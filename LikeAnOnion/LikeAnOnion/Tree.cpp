#include "Tree.h"

Tree::Tree(sf::Texture & t_sceneryTexture)
{
	m_sprite.setTexture(t_sceneryTexture);
	m_sprite.setTextureRect(sf::IntRect(0, 350, 250, 310));
	m_sprite.setScale(0.7, 0.7);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

Tree::~Tree()
{
}

void Tree::initilaize(MyVector3 t_position, Layers t_layer)
{
	m_position = t_position - sf::Vector2f(0,55);
	m_layer = t_layer;

	m_sprite.setPosition(m_position);
	
}

void Tree::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sprite);
}

sf::Sprite * Tree::getBody()
{
	return &m_sprite;
}

Layers Tree::getLayer()
{
	return m_layer;
}
