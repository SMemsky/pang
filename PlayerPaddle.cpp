#include <cassert>
#include <iostream>

#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() :
	m_Velocity(0),
	m_MaxVelocity(800.0f)
{
	Load("res/paddle_new.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle()
{

}

void PlayerPaddle::Draw(sf::RenderWindow& a_Window)
{
	VisibleGameObject::Draw(a_Window);
}

float PlayerPaddle::GetVelocity() const
{
	return m_Velocity;
}

void PlayerPaddle::Update(float deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_Velocity -= 4.5f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_Velocity += 4.5f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_Velocity = 0.0f;
	}

	if(m_Velocity > 1.5f)
	{
		m_Velocity -= 1.5f;
	}
	else
	if(m_Velocity < -1.5f)
	{
		m_Velocity += 1.5f;
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

