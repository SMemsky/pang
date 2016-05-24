#pragma once

#include <SFML/Graphics.hpp>

#include "VisibleGameObject.h"

class Game;

class Paddle : public VisibleGameObject
{
	typedef VisibleGameObject super;
public:
	Paddle(Game* game);
	virtual ~Paddle();

	virtual void update(float deltaTime) override;

	float getVelocity() const;
protected:
	const float m_maxVelocity;
	const float m_acceleration;
	const float m_slowdownRate;
	float m_velocity; // negative -- left, positive -- right

	Game* m_game;
};
