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
	void update(sf::Time dt, Xbox360Controller *t_cont, bool t_collide);
	void render(sf::RenderWindow & t_win, Layers t_currentLayer);
	void move(MyVector3 t_movement);
	void jump();
	void updatePlayerFrame();
	sf::Sprite* getBody();
	Layers getCurrentLayer();
	void checkInput(Xbox360Controller *t_cont, bool t_collide);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	bool * getLandedBool();
	bool * getJumpBool();
	void pushBackToPrevious();

	int getHouseItems();
	int blueprints{ 0 };

private:
	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;

	Layers m_layer;
	sf::Vector2f m_gravity;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Vector2f m_previousPos;
	bool m_landed{ true };
	bool m_jump{ false };

	sf::IntRect m_playerFrame;

	bool walkLeft{ false };
	bool walkRight{ false };

	int animationTimer{ 0 };

};

