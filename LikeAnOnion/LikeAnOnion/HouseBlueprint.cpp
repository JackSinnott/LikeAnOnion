#include "HouseBlueprint.h"

HouseBlueprint::HouseBlueprint(sf::Texture & t_sceneryTexture)
{
	m_sprite.setTexture(t_sceneryTexture);
	m_sprite.setTextureRect(sf::IntRect(0, 843, 80, 57));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

HouseBlueprint::~HouseBlueprint()
{
}

void HouseBlueprint::initilaize(MyVector3 t_position, Layers t_layer)
{
	m_position = t_position - sf::Vector2f(0, 55);
	m_layer = t_layer;

	m_sprite.setPosition(m_position);
}

void HouseBlueprint::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sprite);
}

void HouseBlueprint::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

sf::Sprite * HouseBlueprint::getBody()
{
	return &m_sprite;
}

Layers HouseBlueprint::getLayer()
{
	return m_layer;
}
