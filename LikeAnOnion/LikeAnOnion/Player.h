#pragma once

#include "SFML/Graphics.hpp"
#include "MyVector3.h"
#include "Xbox360Controller.h"
#include "Layer.h"

class Player
{
public:
	Player();
	~Player();
	void update(sf::Time dt, Xbox360Controller *t_cont);
	void render(sf::RenderWindow & t_win, Layers t_currentLayer);
	void move(MyVector3 t_movement);
	void jump();
	void updatePlayerFrame();
	sf::Sprite* getBody();
	Layers getCurrentLayer();
	void checkInput(Xbox360Controller *t_cont);
	sf::Vector2f getPosition();

	int getHouseItems();

private:
	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;
	sf::IntRect m_playerFrame;

	MyVector3 m_position;
	Layers m_layer;

	bool walkLeft{ false };
	bool walkRight{ false };

	int animationTimer{ 0 };

	int houseItems{ 0 };
};

