#pragma once
#include "SFML/Graphics.hpp"
#include "Xbox360Controller.h"

#include "MyVector3.h"

class AboutScreen
{
	sf::Texture m_aboutTexture;
	sf::Sprite m_aboutSprite;
	sf::IntRect m_currentAnimationImage;
	MyVector3 m_position;

	bool buttonPressed = false;
public:

	AboutScreen();
	bool update(sf::Time dt, Xbox360Controller *t_cont);
	void render(sf::RenderWindow & t_win);
	void init();
};

