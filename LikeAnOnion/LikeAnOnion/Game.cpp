#include "Game.h"


GameMode Game::m_gameMode{ GameMode::Licence };




// Contructor
Game::Game() :

	m_renderWin{ sf::VideoMode{ 1600, 1600, 1 }, "Like An Onion" },
	m_forest(5)
{
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

	switch(m_gameMode)					// Switch to control the screens
	{
	case GameMode::Licence:
		m_player.update(t_deltaTime, &m_gameControllerPad);
		m_gameCamera.setCenter(m_player.getPosition());	
		break;
	case GameMode::Splash:
		break;
	case GameMode::Menu:
		break;
	case GameMode::Gameplay:
		break;
	default:
		break;
	}
	m_forest.update(t_deltaTime, m_player.getBody(), m_player.getCurrentLayer());
	

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
		break;
	case GameMode::Gameplay:
		break;
	default:
		break;
	}
	
	//m_renderWin.setView(m_gameCamera);
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