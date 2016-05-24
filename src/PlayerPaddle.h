#pragma once

#include <SFML/Graphics.hpp>

#include "Paddle.h"

class Game;

class PlayerPaddle : public Paddle
{
	typedef Paddle super;
public:
	PlayerPaddle(Game* game);

	void update(float deltaTime) override;
};
