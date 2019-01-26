#include "Game.h"


GameMode Game::m_gameMode{ GameMode::Licence };

// Contructor

Game::Game() :

	m_renderWin{ sf::VideoMode{ 1200, 800, 1 }, "Like An Onion" },
	m_forest(5)
	
{
	// Textures
	m_floorTexture.loadFromFile("floor.jpg");
	m_floor.setTexture(m_floorTexture);
	m_floor.setOrigin(m_floor.getGlobalBounds().width/ 2, m_floor.getGlobalBounds().height / 2);

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

	switch(m_gameMode)					// Switch to control the screens
	{
	case GameMode::Licence:
		m_player.update(t_deltaTime, &m_gameControllerPad);
		m_gameCamera.setCenter(sf::Vector2f{ m_player.getPosition().x, m_player.getPosition().y - 300 });
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
	//m_forest.update(t_deltaTime, m_player.getBody(), m_player.getCurrentLayer());
	for (int i = 0; i < 10; i++)
	{
		if (collision::isCollided(m_grounds[i], *m_player.getBody()))
		{
			m_player.getBody()->setPosition(sf::Vector2f{ m_player.getBody()->getPosition().x,
				m_floor.getPosition().y - (m_grounds[i].getGlobalBounds().height / 2 + m_player.getBody()->getGlobalBounds().height / 2)
			+ static_cast<int>(m_player.getCurrentLayer()) * 20 });
		}
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
		break;
	case GameMode::Gameplay:
		break;
	default:
		break;
	}
	
	for (int i = 0; i < 6; i++)
	{
		m_renderWin.draw(m_sky);
		m_sky.setPosition(m_sky.getPosition().x + m_sky.getGlobalBounds().width, m_sky.getPosition().y);
	}
	m_sky.setPosition(m_floor.getPosition().x, m_floor.getPosition().y - (m_floor.getGlobalBounds().height / 2 + m_sky.getGlobalBounds().height / 2) + 1);

	for (int i = 0; i < 10; i++)
	{
		m_renderWin.draw(m_grounds[i]);
	}
	
	m_renderWin.setView(m_gameCamera);
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