#ifndef MAINMENU
#define MAINMENU

#include <iostream>
#include <string>


enum class MenuState
{
	play, // 0
	about, // 1
	exit //2
};

class MainMenu
{
public:
	MainMenu(); 
	void getSelection();
	void pickYourPoison();
	MenuState m_menuState; // enum data type
};

#endif // !MainMenu