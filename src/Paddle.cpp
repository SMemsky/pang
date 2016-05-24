#include "Paddle.h"

#include <cassert>

#include "Game.h"

Paddle::Paddle(Game* game) :
	super(),
	m_maxVelocity(800.0f),
	m_acceleration(150.0f),
	m_slowdownRate(90.0f),
	m_velocity(0.0f),
	m_game(game)
{
	super::load("res/paddle.png");
	assert(super::isLoaded());

	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2,
		m_sprite.getLocalBounds().height / 2);
}

Paddle::~Paddle()
{}

void Paddle::update(float deltaTime)
{
	// Do collision check and move paddle
	sf::Vector2f pos = super::getPosition();
	float toMove = m_velocity * deltaTime;

	float max = m_game->getScreenWidth();
	// Distance to the left border
	float dl = pos.x - m_sprite.getLocalBounds().width / 2;
	// Distance to the right border
	float dr = max - (pos.x + m_sprite.getLocalBounds().width / 2);
	
	// Check collision with borders
	if (toMove < 0 &&
		dl + toMove < 0)
	{
		m_sprite.move(-dl, 0);
		toMove += dl;
		toMove *= -0.50f;
		m_velocity *= -0.50f;
	}
	else if (toMove > 0 &&
		dr - toMove < 0)
	{
		m_sprite.move(dr, 0);
		toMove -= dr;
		toMove *= -0.50f;
		m_velocity *= -0.50f;
	}

	m_sprite.move(toMove, 0);
}

float Paddle::getVelocity() const
{
	return m_velocity;
}
