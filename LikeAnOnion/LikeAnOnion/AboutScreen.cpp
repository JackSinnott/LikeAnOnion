#include "AboutScreen.h"



AboutScreen::AboutScreen()	:
	m_position{ 0, 0, 0 }

{
	m_aboutTexture.loadFromFile("about.png");
	m_aboutSprite.setTexture(m_aboutTexture);
	m_aboutSprite.setOrigin(m_aboutTexture.getSize().x / 2, m_aboutTexture.getSize().y / 2);
	m_position.x += m_aboutTexture.getSize().x / 2.0f;
	m_position.y += m_aboutTexture.getSize().y / 2.0f;
	m_aboutSprite.setPosition(m_position);
}
bool AboutScreen::update(sf::Time dt, Xbox360Controller * t_cont)
{
	if (t_cont->m_currentState.B == true)
	{
		buttonPressed = true;
	}
	return buttonPressed;
}


void AboutScreen::render(sf::RenderWindow & t_win)
{
	t_win.draw(m_aboutSprite);
}

void AboutScreen::init()
{
	buttonPressed = false;
}


