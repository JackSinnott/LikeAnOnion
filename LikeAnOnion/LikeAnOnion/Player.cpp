#include "Player.h"



Player::Player() : 
	m_position{0,0,0}
	
{
	m_playerTexture.loadFromFile("goat.png");
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setOrigin(m_playerTexture.getSize().x/2, m_playerTexture.getSize().y/2);
}


Player::~Player()
{
}

void Player::update(sf::Time dt, Xbox360Controller *t_cont)
{
	checkInput(t_cont);
}

void Player::render(sf::RenderWindow & t_win)
{
	t_win.draw(m_playerSprite);
}

void Player::move(MyVector3 t_movement)
{
	m_playerSprite.setPosition(m_playerSprite.getPosition() + sf::Vector2f{t_movement});
}

void Player::jump()
{
}

void Player::checkInput(Xbox360Controller *t_cont) 
{
	if (t_cont->m_currentState.DpadRight == true || t_cont->m_currentState.LeftThumbStick.x > 50)
	{
		this->move(sf::Vector2f{ 10, 0 });
	}
	if (t_cont->m_currentState.DpadLeft == true || t_cont->m_currentState.LeftThumbStick.x < -50)
	{
		this->move(sf::Vector2f{ -10, 0 });
	}
	if (t_cont->m_currentState.DpadUp == true || t_cont->m_currentState.LeftThumbStick.y < -50)
	{
		this->move(sf::Vector2f{ 0, -10 });
	}
	if (t_cont->m_currentState.DpadDown == true || t_cont->m_currentState.LeftThumbStick.y > 50)
	{
		this->move(sf::Vector2f{ 0, 10 });
	}
	if (t_cont->m_currentState.A == true)
	{
		// Jump ?
	}
	if (t_cont->m_currentState.B == true)
	{
		// Interact
	}
}

sf::Vector2f Player::getPosition() 
{
	return m_playerSprite.getPosition();
}
