#pragma once



#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Enums.h"
#include "MyVector3.h"
#include "Xbox360Controller.h"

#include "Player.h"
#include "collision.h"

#include "Scenery.h"
#include "MainMenu.h"
#include "AboutScreen.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	static GameMode m_gameMode;

protected:

	Scenery m_forest;

	void intialize();
	void update(sf::Time t_deltaTime);
	void processInput();
	void render();

	MainMenu m_menuScreen;
	AboutScreen m_aboutScreen;


	sf::RenderWindow m_renderWin;
	Xbox360Controller m_gameControllerPad;
	Player m_player;
	sf::View m_gameCamera;


	sf::Texture m_floorTexture;
	sf::Sprite m_floor;
	sf::Sprite m_grounds[10];
	sf::Texture m_skyTexture;
	sf::Sprite m_sky;
	float m_floorHeight;
	bool m_stopPlayer{ false };
	bool objectCollideTree{ false };
	bool objectCollideRock{ false };
	bool objectCollideBP{ false };

	sf::Texture m_houseTexture;

	sf::Sprite m_house;
};

