#pragma once



#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Enums.h"
#include "MyVector3.h"
#include "Xbox360Controller.h"
#include "Player.h"
#include "collision.h"

class Game
{
public:
	Game();
	~Game();

	void run();
	static GameMode m_gameMode;

protected:

	void intialize();
	void update(sf::Time t_deltaTime);
	void processInput();
	void render();

	sf::RenderWindow m_renderWin;
	Xbox360Controller m_gameControllerPad;
	Player m_player;
	sf::View m_gameCamera;
};

