#include "Player.h"



Player::Player() : 
	m_position{100,-100},
	m_layer(Layers::BackLayer),
	m_velocity(0, 0),
	m_gravity(0.0f, 59.8f)
	
{
	m_playerTexture.loadFromFile("goat.png");
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(m_position);
	m_playerSprite.setOrigin(m_playerTexture.getSize().x/2, m_playerTexture.getSize().y/2);
}


Player::~Player()
{
}

void Player::update(sf::Time dt, Xbox360Controller *t_cont)
{
	checkInput(t_cont);
	if (m_landed == false)
	{
		m_velocity = m_velocity + (m_gravity*20.0f) * dt.asSeconds();				// Applying gravity to the ball if it has not landed
		m_position = m_position + m_velocity * dt.asSeconds() + 0.5f*(m_gravity*20.0f)*(dt.asSeconds()*dt.asSeconds());		// Finding the new position each update
	}
	m_playerSprite.setPosition(m_position);
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
	m_position = m_position + sf::Vector2f{t_movement};
}

void Player::jump()
{
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
	if (t_cont->m_currentState.DpadRight == true || t_cont->m_currentState.LeftThumbStick.x > 50)
	{
		this->move(sf::Vector2f{ 10, 0 });
	}
	if (t_cont->m_currentState.DpadLeft == true || t_cont->m_currentState.LeftThumbStick.x < -50)
	{
		this->move(sf::Vector2f{ -10, 0 });
	}
    if (t_cont->m_currentState.A == true && t_cont->m_previousState.A != true && m_landed == true)
	{
		m_velocity = m_velocity + sf::Vector2f(0, -700);
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
