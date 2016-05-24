#include "AIPaddle.h"

#include "Game.h"
#include "GameBall.h"

AIPaddle::AIPaddle(Game* game) :
	super(game)
{}

void AIPaddle::update(float deltaTime)
{
	const GameBall* gameBall = static_cast<GameBall*>(
		m_game->getGameObjectManager().get("Ball_0"));

	float ballPos = gameBall->getPosition().x;
	float myPos = getPosition().x;

	if (myPos + 30 < ballPos)
	{
		if (m_velocity < 0)
		{
			m_velocity = 0;
		}
		else
		{
			m_velocity += 3.0f;	
		}
	}
	else if (myPos - 30 > ballPos)
	{
		if (m_velocity > 0)
		{
			m_velocity = 0;
		}
		else
		{
			m_velocity -= 3.0f;
		}
	}
	else
	{
		m_velocity = 0.0f;
	}

	// Check limits
	m_velocity = (m_velocity > m_maxVelocity) ? m_maxVelocity : m_velocity;
	m_velocity = (-m_velocity > m_maxVelocity) ? -m_maxVelocity : m_velocity;

	super::update(deltaTime);
}
