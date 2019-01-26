#ifndef MAINMENU
#define MAINMENU

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Xbox360Controller.h"
#include <vector>

enum class MenuState
{
	play, // 0
	about, // 1
	exit //2
};

class MainMenu
{
public:
	MainMenu(Xbox360Controller & t_controller);

	Xbox360Controller & m_controller;

	int getSelection();
	MenuState m_menuState; // enum data type

	std::vector<sf::Text> m_buttonsText;
	sf::Font m_font;

	sf::Texture m_buttonTexture;
	std::vector<sf::Sprite> m_buttonSprites;

	bool update();
	void render(sf::RenderWindow &t_window);

	void updateText();

	void handleEnum(bool t_up);

	bool m_switchScreen = false;

	void init();

	// bool to prevent fast scrolling throught the menu
	bool m_dpadPressed = false;
};

#endif // !MainMenu