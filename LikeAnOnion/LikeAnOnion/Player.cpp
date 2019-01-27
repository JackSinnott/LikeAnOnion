#include "Player.h"

Player::Player() :
	m_position{ 100,-100 },
	m_layer(Layers::BackLayer),
	m_velocity(0, 0),
	m_gravity(0.0f, 59.8f)

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

void Player::update(sf::Time dt, Xbox360Controller *t_cont, bool t_collide)
{
	checkInput(t_cont, t_collide);

	if (m_landed == false)
	{
		m_velocity = m_velocity + (m_gravity*20.0f) * dt.asSeconds();				// Applying gravity to the player if it has not landed
		if (t_collide == true)
		{
			m_velocity.x = 0;
		}
		m_previousPos = m_position;
		m_position = m_position + m_velocity * dt.asSeconds() + 0.5f*(m_gravity*20.0f)*(dt.asSeconds()*dt.asSeconds());		// Finding the new position each update
		if (t_collide == true)
		{
			m_position.x = m_previousPos.x;
		}
	}
	else
	{
		m_velocity = { 0,0 };
	}

	m_playerSprite.setPosition(m_position);


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
	m_previousPos = m_position;
	m_position = m_position + sf::Vector2f{ t_movement };
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

void Player::checkInput(Xbox360Controller *t_cont, bool t_collide)
{

	if (t_cont->m_currentState.DpadRight == true || t_cont->m_currentState.LeftThumbStick.x > 50)
	{
		this->move(sf::Vector2f{ 10, 0 });
		walkRight = true;
	}
	if (t_cont->m_currentState.DpadLeft == true || t_cont->m_currentState.LeftThumbStick.x < -50)
	{

		this->move(sf::Vector2f{ -10, 0 });
		walkRight = true;

	}

	if (t_cont->m_currentState.A == true && t_cont->m_previousState.A != true && m_landed == true)
	{
		m_velocity = m_velocity + sf::Vector2f(0, -500);
		m_landed = false;
		m_jump = true;
	}
	if (t_cont->m_currentState.RTrigger > 50 && t_cont->m_previousState.RTrigger < 50)
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
	if (t_cont->m_currentState.LTrigger < -50 && t_cont->m_previousState.LTrigger > -50)
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


void Player::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

bool * Player::getLandedBool()
{
	return &m_landed;
}

bool * Player::getJumpBool()
{
	return &m_jump;
}

void Player::pushBackToPrevious()
{
	m_playerSprite.setPosition(m_previousPos.x, m_position.y);
}

int Player::getHouseItems()
{
	return houseItems;
}
