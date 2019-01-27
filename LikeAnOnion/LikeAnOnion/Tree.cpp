#include "Tree.h"

Tree::Tree(sf::Texture & t_sceneryTexture)
{
	m_spriteLeaves.setTexture(t_sceneryTexture);
	m_spriteLeaves.setTextureRect(sf::IntRect(0, 350, 250, 210));
	m_spriteLeaves.setScale(0.7, 0.7);
	m_spriteLeaves.setOrigin(m_spriteLeaves.getGlobalBounds().width / 2, m_spriteLeaves.getGlobalBounds().height / 2);
	m_spriteTrunk.setTexture(t_sceneryTexture);
	m_spriteTrunk.setTextureRect(sf::IntRect(80, 560, 72, 100));
	m_spriteTrunk.setScale(0.7, 0.7);
	m_spriteTrunk.setOrigin(m_spriteTrunk.getGlobalBounds().width / 2, m_spriteTrunk.getGlobalBounds().height / 2);

}

Tree::~Tree()
{
}

void Tree::initilaize(MyVector3 t_position, Layers t_layer)
{
	m_position = t_position - sf::Vector2f(0,80);
	m_layer = t_layer;

	m_spriteLeaves.setPosition(m_position);
	m_spriteTrunk.setPosition(m_position.x + 12, m_position.y + 120);
	
}

void Tree::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_spriteLeaves);
	t_window.draw(m_spriteTrunk);
}

sf::Sprite * Tree::getSpriteLeaves()
{
	return &m_spriteLeaves;
}

sf::Sprite * Tree::getSpriteTrunk()
{
	return &m_spriteTrunk;
}

Layers Tree::getLayer()
{
	return m_layer;
}
