#include "Game.h"


GameMode Game::m_gameMode{ GameMode::Gameplay };

// Contructor

Game::Game() :

	m_renderWin{ sf::VideoMode{ 1200, 800, 1 }, "Like An Onion" },
	m_forest(5),
	m_menuScreen(m_gameControllerPad),
	m_floorHeight(-160)


{
	// Textures
	m_floorTexture.loadFromFile("floor.png");
	m_floor.setTexture(m_floorTexture);
	m_floor.setOrigin(m_floor.getGlobalBounds().width / 2, m_floor.getGlobalBounds().height / 2);

	for (int i = 0; i < 10; i++)
	{
		m_grounds[i].setTexture(m_floorTexture);
		m_grounds[i].setOrigin(m_floor.getGlobalBounds().width / 2, m_floor.getGlobalBounds().height / 2);
		m_grounds[i].setPosition(0 + i * 3070, 0);
	}

	m_skyTexture.loadFromFile("dubSky.png");
	m_sky.setTexture(m_skyTexture);
	m_sky.setOrigin(m_sky.getGlobalBounds().width / 2, m_sky.getGlobalBounds().height / 2);
	m_sky.setPosition(m_floor.getPosition().x, m_floor.getPosition().y - (m_floor.getGlobalBounds().height / 2 + m_sky.getGlobalBounds().height / 2) + 1);
	m_gameCamera.setSize(1200, 800);
}

/// Destructor
Game::~Game()
{
}

// Loop designed to work at equal speed on all PCs
// If a PC is slower, it will update the same amount of times
// And render less often
void Game::run()
{
	sf::Clock gameClock;											// Game clock
	sf::Time timeTakenForUpdate = sf::Time::Zero;					// No lag on first input
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);				// 60 frames per second
	while (m_renderWin.isOpen())									// Loop
	{
		processInput();												// Check for input
		timeTakenForUpdate += gameClock.restart();					// Returns time take to do the loop
		while (timeTakenForUpdate > timePerFrame)					// Update enough times to catch up on updates missed during the lag time
		{
			timeTakenForUpdate -= timePerFrame;						// Decrement lag
			processInput();											// More checks, more accuracte input to display will be
			update(timePerFrame);									// Update
		}
		render();
	}
}


// Process PC input
void Game::processInput()
{
	sf::Event event;
	while (m_renderWin.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_renderWin.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_renderWin.close();
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
		}
	}
}

// Updates Game
void Game::update(sf::Time t_deltaTime)
{
	m_gameControllerPad.update();

	switch (m_gameMode)					// Switch to control the screens
	{
	case GameMode::Licence:
		break;
	case GameMode::Splash:
		break;
		if (m_menuScreen.update()) {
			if (m_menuScreen.getSelection() == 1) {
				m_gameMode = GameMode::Gameplay;
			}
			else if (m_menuScreen.getSelection() == 2) {
				m_gameMode = GameMode::About;
				m_aboutScreen.init();
			}
			else if (m_menuScreen.getSelection() == 3) {
				m_renderWin.close();
			}
		}
		break;
	case GameMode::Gameplay:

		break;
	case GameMode::About:
		if (m_aboutScreen.update(t_deltaTime, &m_gameControllerPad)) {
			m_gameMode = GameMode::Menu;
			m_menuScreen.init();
		}
		break;
	default:
		break;
	}

	m_player.update(t_deltaTime, &m_gameControllerPad, objectCollideTree);
	m_gameCamera.setCenter(sf::Vector2f{ m_player.getPosition().x, m_player.getPosition().y - 300 });

	// tree collide
	objectCollideTree = m_forest.checkCollisions(m_player.getBody(),m_player.getCurrentLayer(), 1 );
	objectCollideRock = m_forest.checkCollisions(m_player.getBody(), m_player.getCurrentLayer(), 2);

	if (objectCollideTree == true)
	{
		m_player.pushBackToPrevious();
	}
	
	Layers m_currentLayer = m_player.getCurrentLayer();
	if (m_currentLayer == Layers::BackLayer)
	{
		m_floorHeight = -140;
	}
	else if (m_currentLayer == Layers::MiddleLayer)
	{
		m_floorHeight = -120;
	}
	else if (m_currentLayer == Layers::FrontLayer)
	{
		m_floorHeight = -100;
	}
	if (m_player.getPosition().y > m_floorHeight)
	{
		*m_player.getLandedBool() = true;
	}

	if (*m_player.getLandedBool() == true)
	{
		m_player.setPosition(sf::Vector2f{ m_player.getBody()->getPosition().x, m_floorHeight });
	}
	else
	{
		m_player.setPosition(sf::Vector2f{ m_player.getBody()->getPosition().x, m_player.getBody()->getPosition().y });
	}
}



// Renders
void Game::render()
{
	m_renderWin.clear();
	switch (m_gameMode)					// Swtich to control the screens
	{
	case GameMode::Licence:
		break;
	case GameMode::Splash:
		break;
	case GameMode::Menu:
		m_menuScreen.render(m_renderWin);
		break;
	case GameMode::Gameplay:
		break;
	case GameMode::About:
		m_aboutScreen.render(m_renderWin);
		break;
	default:
		break;
	}
	m_renderWin.setView(m_gameCamera);

	for (int i = 0; i < 6; i++)
	{
		m_renderWin.draw(m_sky);
		m_sky.setPosition(m_sky.getPosition().x + m_sky.getGlobalBounds().width, m_sky.getPosition().y);
	}
	m_sky.setPosition(m_floor.getPosition().x, m_floor.getPosition().y - (m_floor.getGlobalBounds().height / 2 + m_sky.getGlobalBounds().height / 2) + 1); // Reset

	for (int i = 0; i < 10; i++)
	{
		m_renderWin.draw(m_grounds[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		m_forest.render(m_renderWin, static_cast<Layers>(i));
		m_player.render(m_renderWin, static_cast<Layers>(i));  // Player after items becuase it needs to be on top it's current layer 
	}

	m_renderWin.display();
}

void Game::intialize()
{
}