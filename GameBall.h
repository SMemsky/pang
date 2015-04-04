#pragma once

#include "VisibleGameObject.h"

class GameBall : public VisibleGameObject
{
public:
	
	GameBall();
	virtual ~GameBall();

	void Update(float deltaTime);

private:
	float m_Velocity;
	float m_Angle;
	float m_Runtime;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);

};
