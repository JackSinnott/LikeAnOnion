#include "Rock.h"

Rock::Rock(sf::Texture & t_sceneryTexture)
{
	m_sprite.setTexture(t_sceneryTexture);
	m_sprite.setTextureRect(sf::IntRect(161, 297, 50, 44));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

Rock::~Rock()
{
}

void Rock::initilaize(MyVector3 t_position, Layers t_layer)
{
	m_position = t_position;
	m_layer = t_layer;

	m_sprite.setPosition(m_position);
}

void Rock::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sprite);
}

sf::Sprite * Rock::getBody()
{
	return &m_sprite;
}

Layers Rock::getLayer()
{
	return m_layer;
}
