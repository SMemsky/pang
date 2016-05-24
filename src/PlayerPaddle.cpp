#include "PlayerPaddle.h"

#include <iostream>

PlayerPaddle::PlayerPaddle(Game* game) :
	super(game)
{}

void PlayerPaddle::update(float deltaTime)
{
	// Catch input
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_velocity -= m_acceleration * deltaTime;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_velocity += m_acceleration * deltaTime;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_velocity = 0.0f;
	}
/*
	// Slow down
	if(m_velocity > 1.5f)
	{
		m_velocity -= 1.5f;
	}
	else if(m_velocity < -1.5f)
	{
		m_velocity += 1.5f;
	}
	else
	{
		m_velocity = 0.0f;
	}
*/
	//m_velocity *= 0.999f;

	// Check limits
	m_velocity = (m_velocity > m_maxVelocity) ? m_maxVelocity : m_velocity;
	m_velocity = (-m_velocity > m_maxVelocity) ? -m_maxVelocity : m_velocity;

	super::update(deltaTime);
}
