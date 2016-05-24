#pragma once

#include <SFML/Graphics.hpp>

#include "GameObjectManager.h"

class Game
{
public:
	Game();
	~Game();

	bool init();
	void start();

	int getScreenWidth() const;
	int getScreenHeight() const;

	const GameObjectManager& getGameObjectManager() const;
private:
	bool isExiting() const;
	void gameLoop(float deltaTime);

	void showSplash();
	void showMenu();
private:
	enum GameState
	{
		Uninitialized,
		Initialized,
		ShowingSplash,
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};
private:
	GameState m_gameState;
	sf::RenderWindow m_window;

	GameObjectManager m_gameObjectManager;

	const int m_screenWidth;
	const int m_screenHeight;
};
