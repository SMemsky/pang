#include "GameBall.h"

#include <iostream>
#include <cassert>
#include <cmath>

#include "Game.h"
#include "Paddle.h"

GameBall::GameBall(Game* game) :
	super(),
	m_velocity(2300.0f),
	m_angle(std::rand() % 360 + 1),
	m_runtime(0.0f),
	m_game(game)
{
	super::load("res/ball.png");
	assert(super::isLoaded());

	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2,
		m_sprite.getLocalBounds().height / 2);
}

void GameBall::update(float deltaTime)
{
	m_runtime += deltaTime;
	if (m_runtime < 0.0f)
	{
		return;
	}

	Paddle* player = dynamic_cast<Paddle*>(
		m_game->getGameObjectManager().get("Paddle_0"));
	Paddle* ai = dynamic_cast<Paddle*>(
		m_game->getGameObjectManager().get("AI_0"));

	assert(player != nullptr);
	assert(ai != nullptr);

	float moveDist = m_velocity * deltaTime;
	float moveByX = linearVelocityX(m_angle) * moveDist;
	float moveByY = linearVelocityY(m_angle) * moveDist;


	sf::Rect<float> playerBB = player->getBoundingRect();
	sf::Rect<float> aiBB = ai->getBoundingRect();

	if (playerBB.intersects(getBoundingRect()))
	{
		m_angle = 360.0f - (m_angle - 180.0f);
		if (m_angle > 360.0f)
		{
			m_angle -= 360.f;
		}

		moveByY = -moveByY;

		// Make sure ball isn't inside paddle
		if(getBoundingRect().width > player->getBoundingRect().top)
		{
			setPosition(getPosition().x,player->getBoundingRect().top - getWidth()/2 -1 );
		}

		// Now add "English" based on the players velocity.  
		float playerVelocity = player->getVelocity();
	
		if(playerVelocity < 0)
		{
			// moving left
			m_angle -= 20.0f;
			if(m_angle < 0 ) m_angle = 360.0f - m_angle;
		}
		else if(playerVelocity > 0)
		{
			m_angle += 20.0f;
			if(m_angle > 360.0f) m_angle = m_angle - 360.0f;
		}

		m_velocity += 5.0f;
	}
	else if (aiBB.intersects(getBoundingRect()))
	{
		m_angle = 360.0f - (m_angle - 180.0f);
		if (m_angle > 360.0f)
		{
			m_angle -= 360.f;
		}

		moveByY = -moveByY;

		// Make sure ball isn't inside paddle
		if(getBoundingRect().width > ai->getBoundingRect().height)
		{
			setPosition(getPosition().x, ai->getBoundingRect().height - getWidth()/2 -1 );
		}

		// Now add "English" based on the ai velocity.  
		float aiVelocity = ai->getVelocity();
	
		if(aiVelocity < 0)
		{
			// moving left
			m_angle -= 20.0f;
			if(m_angle < 0 ) m_angle = 360.0f - m_angle;
		}
		else if(aiVelocity > 0)
		{
			m_angle += 20.0f;
			if(m_angle > 360.0f) m_angle = m_angle - 360.0f;
		}

		m_velocity += 5.0f;
	}

	float max = m_game->getScreenWidth();
	// Distance to right border
	float dr = max - (getPosition().x + getWidth() / 2);
	// Distance to left border
	float dl = getPosition().x - getWidth() / 2;

	if (dr - moveByX < 0 ||
		dl + moveByX < 0)
	{
		m_angle = 360.0f - m_angle;
		if(m_angle > 260.0f && m_angle < 280.0f)
		{
			m_angle += 20.0f;
		}
		if(m_angle > 80.0f && m_angle < 100.0f)
		{
			m_angle += 20.0f;
		}

		moveByX = -moveByX;
	}

	// Distance to bottom
	max = m_game->getScreenHeight();
	float db = max - (getPosition().y + getHeight() / 2);
	// Distance to top
	float dt = getPosition().y - getHeight() / 2;

	if (db - moveByY < 0 ||
		dt + moveByY < 0)
	{
		// move to middle of the screen for now and randomize angle
		m_sprite.setPosition(m_game->getScreenWidth() / 2,
			m_game->getScreenHeight() / 2);
		m_angle = (rand()%360) + 1;
		m_velocity = 2300.0f;
		m_runtime = 0.0f;
	}

	m_sprite.move(moveByX,moveByY);
}

float GameBall::linearVelocityX(float angle) const
{
	angle -= 90;
	if (angle < 0)
	{
		angle += 360;
	}

	return std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::linearVelocityY(float angle) const
{
	angle -= 90;
	if (angle < 0)
	{
		angle += 360;
	}

	return std::sin(angle * (3.1415926 / 180.0f));
}
