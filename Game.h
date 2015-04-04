#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerPaddle.h"
#include "GameBall.h"
#include "AIPaddle.h"
#include "GameObjectManager.h"

class Game
{
public:
	Game();
	~Game();

	void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();
	static GameObjectManager& GetGameObjectManager();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:

	bool IsExiting();
	void GameLoop();

	void ShowSplash();
	void ShowMenu();

	enum GameState
	{
		Uninitialized,
		ShowingSplash,
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};

	GameState m_GameState;
	static sf::RenderWindow m_Window;

	static GameObjectManager m_GameObjectManager;
};
