#pragma once

#include "Paddle.h"

class Game;

class AIPaddle : public Paddle
{
	typedef Paddle super;
public:
	AIPaddle(Game* game);

	void update(float deltaTime) override;
};
