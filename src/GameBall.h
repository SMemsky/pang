#pragma once

#include "VisibleGameObject.h"

class Game;

class GameBall : public VisibleGameObject
{
	typedef VisibleGameObject super;
public:
	GameBall(Game* game);

	void update(float deltaTime);
private:
	float linearVelocityX(float angle) const;
	float linearVelocityY(float angle) const;
private:
	float m_velocity;
	float m_angle;
	float m_runtime;

	Game* m_game;
};
