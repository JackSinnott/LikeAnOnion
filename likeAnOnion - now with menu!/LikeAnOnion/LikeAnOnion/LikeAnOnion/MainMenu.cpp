#include "MainMenu.h"



MainMenu::MainMenu()
{
	menu = menuState::play;
	menu = menuState::about;
	menu = menuState::exit;
}

void MainMenu::getSelection()
{
	switch (menu)
	{
	case menuState::play:
		std::cout << "Start Game \n";
		break;
	case menuState::about:
		std::cout << "About Game \n";
		break;
	case menuState::exit:
		std::cout << "Exit Game \n";
		break;
	default:
		break;
	}
}

