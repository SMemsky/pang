#include <cassert>

#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"

AIPaddle::AIPaddle() :
	m_Velocity(0.0f),
	m_MaxVelocity(800.0f)
{
	Load("res/paddle_new.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2);
}

AIPaddle::~AIPaddle()
{

}

void AIPaddle::Update(float deltaTime)
{
	const GameBall* gameBall = static_cast<GameBall*>(Game::GetGameObjectManager().Get("Ball0"));

	float ballPos = gameBall->GetPosition().x;
	float myPos = GetPosition().x;

	if (myPos + 30 < ballPos)
	{
		if (m_Velocity < 0)
		{
			m_Velocity = 0;
		}
		else
		{
			m_Velocity += 3.0f;	
		}
	}
	else if (myPos - 30 > ballPos)
	{
		if (m_Velocity > 0)
		{
			m_Velocity = 0;
		}
		else
		{
			m_Velocity -= 3.0f;
		}
	}
	else
	{
		m_Velocity = 0.0f;
	}

	if(m_Velocity > m_MaxVelocity)
	{
		m_Velocity = m_MaxVelocity;
	}

	if(m_Velocity < -(m_MaxVelocity))
	{
		m_Velocity = -(m_MaxVelocity);
	}

	sf::Vector2f pos = this->GetPosition();
	float toMove = m_Velocity * deltaTime;

	if(pos.x + toMove < GetSprite().getLocalBounds().width / 2)
	{
		m_Velocity = -(m_Velocity); // Bounce by current velocity in opposite direction
	}
	if(pos.x + toMove > (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2))
	{
		m_Velocity = -(m_Velocity);
	}

	GetSprite().move(toMove, 0);
}

void AIPaddle::Draw(sf::RenderWindow& a_Window)
{
	VisibleGameObject::Draw(a_Window);
}

float AIPaddle::GetVelocity() const
{
	return m_Velocity;
}
