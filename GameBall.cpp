#include <cassert>
#include <iostream>
#include <cmath>

#include "GameBall.h"
#include "Game.h"

GameBall::GameBall() :
	m_Velocity(230.0f),
	m_Runtime(0.0f)
{
	Load("res/ball_new.png");
	assert(IsLoaded());

	GetSprite().setOrigin(15, 15);

	m_Angle = std::rand() % 360 + 1;
}

GameBall::~GameBall()
{

}

void GameBall::Update(float deltaTime)
{
	m_Runtime += deltaTime;

	if (m_Runtime < 3.0f)
	{
		return;
	}

	float moveDist = m_Velocity * deltaTime;

	float moveByX = LinearVelocityX(m_Angle) * moveDist;
	float moveByY = LinearVelocityY(m_Angle) * moveDist;

	//collide with the left side of the screen
	if(GetPosition().x + moveByX <= 0 + GetWidth() / 2 
		|| GetPosition().x + GetHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
	{
		//Ricochet!
		m_Angle = 360.0f - m_Angle;
		if(m_Angle > 260.0f && m_Angle < 280.0f)
		{
			m_Angle += 20.0f;
		}
		if(m_Angle > 80.0f && m_Angle < 100.0f)
		{
			m_Angle += 20.0f;
		}

		moveByX = -moveByX;
	}

	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
	AIPaddle* ai1 = dynamic_cast<AIPaddle*>(Game::GetGameObjectManager().Get("AI1"));
	if (player1 != NULL && ai1 != NULL)
	{
		sf::Rect<float> p1BB = player1->GetBoundingRect();
		sf::Rect<float> ai1BB = ai1->GetBoundingRect();

		if (p1BB.intersects(GetBoundingRect()))
		{
			m_Angle = 360.0f - (m_Angle - 180.0f);
			if (m_Angle > 360.0f)
			{
				m_Angle -= 360.f;
			}

			moveByY = -moveByY;

			// Make sure ball isn't inside paddle
			if(GetBoundingRect().width > player1->GetBoundingRect().top)
			{
				SetPosition(GetPosition().x,player1->GetBoundingRect().top - GetWidth()/2 -1 );
			}

			// Now add "English" based on the players velocity.  
			float playerVelocity = player1->GetVelocity();
		
			if(playerVelocity < 0)
			{
				// moving left
				m_Angle -= 20.0f;
				if(m_Angle < 0 ) m_Angle = 360.0f - m_Angle;
			}
			else if(playerVelocity > 0)
			{
				m_Angle += 20.0f;
				if(m_Angle > 360.0f) m_Angle = m_Angle - 360.0f;
			}

			m_Velocity += 5.0f;
		}
		else if (ai1BB.intersects(GetBoundingRect()))
		{
			m_Angle = 360.0f - (m_Angle - 180.0f);
			if (m_Angle > 360.0f)
			{
				m_Angle -= 360.f;
			}

			moveByY = -moveByY;

			// Make sure ball isn't inside paddle
			if(GetBoundingRect().width > ai1->GetBoundingRect().height)
			{
				SetPosition(GetPosition().x, ai1->GetBoundingRect().height - GetWidth()/2 -1 );
			}

			// Now add "English" based on the ai velocity.  
			float aiVelocity = ai1->GetVelocity();
		
			if(aiVelocity < 0)
			{
				// moving left
				m_Angle -= 20.0f;
				if(m_Angle < 0 ) m_Angle = 360.0f - m_Angle;
			}
			else if(aiVelocity > 0)
			{
				m_Angle += 20.0f;
				if(m_Angle > 360.0f) m_Angle = m_Angle - 360.0f;
			}

			m_Velocity += 5.0f;
		}
		
		
		//if(GetPosition().y - GetSprite().GetSize().y/2 - moveByY <= 0 || GetPosition().y + GetSprite().GetSize().y/2 + moveByY >= Game::SCREEN_HEIGHT)
		if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGHT)
		{
			// move to middle of the screen for now and randomize angle
			GetSprite().setPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
			m_Angle = (rand()%360)+1;
			m_Velocity = 230.0f;
			m_Runtime = 0.0f;
		}
		else if (GetPosition().y - GetHeight() / 2 + moveByY <= 0)
		{
			GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
			m_Angle = (rand()%360)+1;
			m_Velocity = 230.0f;
			m_Runtime = 0.0f;
		}
		

		/*
		if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGHT)
		{
			std::cout << m_Angle << std::endl;
			m_Angle = 180 - m_Angle;
			moveByY = -moveByY;
		}
		*/

		GetSprite().move(moveByX,moveByY);
	}
}

float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0)
	{
		angle += 360;
	}

	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0)
	{
		angle += 360;
	}

	return (float)std::sin(angle * (3.1415926 / 180.0f));
}
