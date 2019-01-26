#pragma once

#include "SFML/Graphics.hpp"
#include "MyVector3.h"
#include "Xbox360Controller.h"

class Player
{
public:
	Player();
	~Player();
	void update(sf::Time dt, Xbox360Controller *t_cont);
	void render(sf::RenderWindow & t_win);
	void move(MyVector3 t_movement);
	void jump();
	void checkInput(Xbox360Controller *t_cont);
	sf::Vector2f getPosition();

private:
	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;
	sf::IntRect m_currentAnimationImage;
	MyVector3 m_position;
	

};

