#include "Menu.h"



MainMenu::MainMenu(Xbox360Controller & t_controller) :
	m_controller(t_controller)
{
	m_menuState = MenuState::play;

	m_buttonTexture.loadFromFile("Button.png");
	m_font.loadFromFile("ariblk.ttf");

	for (int i = 0; i < 3; i++)
	{
		sf::Text text;
		sf::Sprite sprite;

		// push text and sprite into vectors
		m_buttonSprites.push_back(sprite);
		m_buttonsText.push_back(text);

		// set font and colour
		m_buttonsText[i].setFont(m_font);
		m_buttonsText[i].setFillColor(sf::Color::White);

		// set texture
		m_buttonSprites[i].setTexture(m_buttonTexture);

		//set origin
		m_buttonSprites[i].setOrigin(m_buttonTexture.getSize().x / 2, m_buttonTexture.getSize().y / 2);

		// set position
		m_buttonSprites[i].setPosition(sf::Vector2f(1600.f * 0.5f, 1600.f * (0.25f * (i + 1))));
	}
	// set play button as selected
	m_buttonsText[0].setFillColor(sf::Color::Red);

	// set string for all buttons
	m_buttonsText[0].setString("Play Game");
	m_buttonsText[1].setString("About");
	m_buttonsText[2].setString("Exit");

	// set button text on top of the sprites
	for (int i = 0; i < m_buttonsText.size(); i++)
	{
		sf::Vector2f center = sf::Vector2f(m_buttonsText[i].getLocalBounds().width / 2.0f, m_buttonsText[i].getLocalBounds().height / 2.0f);

		m_buttonsText[i].setOrigin(center);
		m_buttonsText[i].setPosition(sf::Vector2f(1600.f * 0.5f, 1600.f * (0.25f * (i + 1))));

	}
}

int MainMenu::getSelection()
{
	// return an int for which button was selected in the menu
	int goToScreen = 0;
	switch (m_menuState)
	{
	case MenuState::play:
		std::cout << "Play selected" << std::endl;
		goToScreen = 1;
		break;
	case MenuState::about:
		std::cout << "About Game selected" << std::endl;
		goToScreen = 2;
		break;
	case MenuState::exit:
		std::cout << "Exit Game selected" << std::endl;
		goToScreen = 3;
		break;
	default:
		break;
	}
	return goToScreen;
}

bool MainMenu::update()
{
	if (m_controller.m_currentState.DpadUp && !m_dpadPressed)
	{
		m_dpadPressed = true;
		handleEnum(true);
	}
	else if (m_controller.m_currentState.DpadDown && !m_dpadPressed)
	{
		m_dpadPressed = true;
		handleEnum(false);
	}
	else if(!m_controller.m_currentState.DpadUp && !m_controller.m_currentState.DpadDown){
		m_dpadPressed = false;
	}

	updateText();

	if (m_controller.m_currentState.A)
	{
		m_switchScreen = true;
	}

	return m_switchScreen;
}

void MainMenu::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < m_buttonSprites.size(); i++)
	{
		t_window.draw(m_buttonSprites[i]);
		t_window.draw(m_buttonsText[i]);
	}
}



void MainMenu::updateText()
{
	// set colours for all button texts
	switch (m_menuState)
	{
	case MenuState::play:
		m_buttonsText[0].setFillColor(sf::Color::Red);
		m_buttonsText[1].setFillColor(sf::Color::Black);
		m_buttonsText[2].setFillColor(sf::Color::Black);
		break;
	case MenuState::about:
		m_buttonsText[0].setFillColor(sf::Color::Black);
		m_buttonsText[1].setFillColor(sf::Color::Red);
		m_buttonsText[2].setFillColor(sf::Color::Black);
		break;
	case MenuState::exit:
		m_buttonsText[0].setFillColor(sf::Color::Black);
		m_buttonsText[1].setFillColor(sf::Color::Black);
		m_buttonsText[2].setFillColor(sf::Color::Red);
		break;
	default:
		break;
	}

}

void MainMenu::handleEnum(bool t_up)
{
	if (t_up)
	{
		switch (m_menuState)
		{
		case MenuState::play:
			m_menuState = MenuState::exit;
			break;
		case MenuState::about:
			m_menuState = MenuState::play;
			break;
		case MenuState::exit:
			m_menuState = MenuState::about;
			break;
		default:
			break;
		}
	}
	else {
		switch (m_menuState)
		{
		case MenuState::play:
			m_menuState = MenuState::about;
			break;
		case MenuState::about:
			m_menuState = MenuState::exit;
			break;
		case MenuState::exit:
			m_menuState = MenuState::play;
			break;
		default:
			break;
		}
	}
}

// init bool when re-entering the main menu
void MainMenu::init()
{
	m_switchScreen = false;
	m_dpadPressed = false;
}
