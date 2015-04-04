#include <SFML/Graphics.hpp>
#include <string>

#include "Game.h"
#include "Splash.h"
#include "MainMenu.h"

sf::RenderWindow Game::m_Window;
GameObjectManager Game::m_GameObjectManager;

Game::Game()
{
	m_GameState = Uninitialized;

}

Game::~Game()
{

}

void Game::Start()
{
	if (m_GameState != Uninitialized)
	{
		return;
	}

	m_Window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "PANG!");

	PlayerPaddle* m_Player1 = new PlayerPaddle();
	m_Player1->SetPosition((SCREEN_WIDTH / 2), 700);
	m_GameObjectManager.Add("Paddle1", m_Player1);

	AIPaddle* m_AI = new AIPaddle();
	m_AI->SetPosition((SCREEN_WIDTH / 2), 40);
	m_GameObjectManager.Add("AI1", m_AI);

	GameBall* m_Ball = new GameBall();
	m_Ball->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2) + 30);
	m_GameObjectManager.Add("Ball0", m_Ball);


	m_GameState = ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	m_Window.close();
}

bool Game::IsExiting()
{
	return m_GameState == Exiting;
}

GameObjectManager& Game::GetGameObjectManager()
{
	return Game::m_GameObjectManager;
}

sf::RenderWindow& Game::GetWindow()
{
	return Game::m_Window;
}

const sf::Event& Game::GetInput() 
{
	static sf::Event event;
	Game::m_Window.pollEvent(event);
	return event;
}

void Game::GameLoop()
{
	switch(m_GameState)
	{
		case ShowingMenu:
		{
			ShowMenu();
			break;
		}
		case ShowingSplash:
		{
			ShowSplash();
			break;
		}
		case Paused:
		{
			break;
		}
		case Exiting:
		{
			break;
		}
		case Uninitialized:
		{
			break;
		}
		case Playing:
		{
			sf::Event event;

			while (m_Window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_GameState = Exiting;
				}
			}

			m_GameObjectManager.UpdateAll();
			
			m_Window.clear(sf::Color(0,0,0));
			m_Window.pushGLStates();
			m_GameObjectManager.DrawAll(m_Window);
			m_Window.popGLStates();
			m_Window.display();

			break;
		}
	}
}

void Game::ShowSplash()
{
	SplashScreen splash;
	splash.Show(m_Window);
	m_GameState = ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(m_Window);

	if (result == MainMenu::Exit)
	{
		m_GameState = Exiting;
		return;
	}
	else if (result == MainMenu::Play)
	{
		m_GameState = Playing;
		return;
	}
}
