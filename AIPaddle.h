#pragma once

#include "VisibleGameObject.h"

class AIPaddle : public VisibleGameObject
{
public:
	AIPaddle();
	~AIPaddle();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& a_Window);

	float GetVelocity() const;

private:
	float m_Velocity; //-- left, ++ right
	float m_MaxVelocity;
};
