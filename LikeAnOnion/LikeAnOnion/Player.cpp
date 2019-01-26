#include "Player.h"

Player::Player() : 
	m_position{100,-100,0},
	m_layer(Layers::BackLayer)	
{
	m_playerTexture.loadFromFile("ASSETS/Player.png");
	m_playerSprite.setTexture(m_playerTexture);
	m_playerFrame = sf::IntRect(0, 3 * 65, 60, 65);
	m_playerSprite.setTextureRect(m_playerFrame);
	m_playerSprite.setPosition(m_position);
	m_playerSprite.setOrigin(m_playerFrame.width / 2, m_playerFrame.height / 2);
}

Player::~Player()
{
}

void Player::update(sf::Time dt, Xbox360Controller *t_cont)
{
	checkInput(t_cont);
	updatePlayerFrame();
}

void Player::render(sf::RenderWindow & t_win, Layers t_currentLayer)
{
	if (m_layer == t_currentLayer)
	{
		t_win.draw(m_playerSprite);
	}
}

void Player::move(MyVector3 t_movement)
{
	m_playerSprite.setPosition(m_playerSprite.getPosition() + sf::Vector2f{t_movement});
}

void Player::jump()
{
}

void Player::updatePlayerFrame()
{
	//If we have moved right we animate walking right.
	if (walkRight == true)
	{
		//If the animation timer reached 0.
		if (animationTimer == 0)
		{
			//If we have reached the end of the sprite sheet we go back to the start.
			if (m_playerFrame.left == 540)
			{
				m_playerFrame.left = 0;
			}
			//Jump to the next frame in line.
			m_playerFrame.left = m_playerFrame.left + m_playerFrame.width;

			//Sets the y frame.
			m_playerFrame.top = 455;

			//Reset the animation timer back to max.
			animationTimer = 4;
		}
		animationTimer--;
	}
	else if (walkLeft == true)
	{
		if (animationTimer == 0)
		{
			if (m_playerFrame.left == 0)
			{
				m_playerFrame.left = 540;
			}
			m_playerFrame.left = m_playerFrame.left - m_playerFrame.width;
			m_playerFrame.top = 325;
			animationTimer = 4;
		}
		animationTimer--;
	}
	else
	{
		//We are not not moving so we do the idle animation.
		m_playerFrame = sf::IntRect(0, 3 * 65, 60, 65);
	}

	m_playerSprite.setTextureRect(m_playerFrame);
	walkLeft = false;
	walkRight = false;
}

sf::Sprite * Player::getBody()
{
	return &m_playerSprite;
}

Layers Player::getCurrentLayer()
{
	return m_layer;
}

void Player::checkInput(Xbox360Controller *t_cont) 
{
	this->move(sf::Vector2f{ 10, 0 });
	walkRight = true;
	if (t_cont->m_currentState.DpadRight == true || t_cont->m_currentState.LeftThumbStick.x > 50)
	{
		this->move(sf::Vector2f{ 10, 0 });
		walkRight = true;
	}
	if (t_cont->m_currentState.DpadLeft == true || t_cont->m_currentState.LeftThumbStick.x < -50)
	{
		this->move(sf::Vector2f{ -10, 0 });
		walkLeft = true;
	}
	/*if (t_cont->m_currentState.DpadUp == true || t_cont->m_currentState.LeftThumbStick.y < -50)
	{
		this->move(sf::Vector2f{ 0, -10 });
	}
	if (t_cont->m_currentState.DpadDown == true || t_cont->m_currentState.LeftThumbStick.y > 50)
	{
		this->move(sf::Vector2f{ 0, 10 });
	}*/
	if (t_cont->m_currentState.A == true && t_cont->m_previousState.A == false)
	{
		if (m_layer == Layers::FrontLayer)
		{
			m_layer = Layers::MiddleLayer;
		}
		else if (m_layer == Layers::MiddleLayer)
		{
			m_layer = Layers::BackLayer;
		}
	}
	if (t_cont->m_currentState.B == true && t_cont->m_previousState.B == false)
	{
		if (m_layer == Layers::MiddleLayer)
		{
			m_layer = Layers::FrontLayer;
		}
		else if (m_layer == Layers::BackLayer)
		{
			m_layer = Layers::MiddleLayer;
		}
	}
	t_cont->m_previousState = t_cont->m_currentState;
}

sf::Vector2f Player::getPosition() 
{
	return m_playerSprite.getPosition();
}

int Player::getHouseItems()
{
	return houseItems;
}
