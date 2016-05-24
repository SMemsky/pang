#include "Game.h"

#include "Splash.h"
#include "MainMenu.h"

#include "PlayerPaddle.h"
#include "GameBall.h"
#include "AIPaddle.h"

Game::Game() :
	m_gameState(Uninitialized),
	m_window(),
	m_gameObjectManager(),
	m_screenWidth(1024),
	m_screenHeight(768)
{}

Game::~Game()
{}

bool Game::init()
{
	if (m_gameState != Uninitialized)
	{
		return false;
	}

	// FIXME: Resizing will break things
	// TODO: Disable resizing?
	// Or rewrite everything? xD

	// Create window
	m_window.create(sf::VideoMode(m_screenWidth, m_screenHeight),
		"Pang updated");

	// Add main game objects (there can be multiple balls!)
	// TODO: Position is related to window size. Improve this
	PlayerPaddle* player0 = new PlayerPaddle(this);
	player0->setPosition((m_screenWidth / 2), 700);
	m_gameObjectManager.add("Paddle_0", player0);

	AIPaddle* opponent = new AIPaddle(this);
	opponent->setPosition((m_screenWidth / 2), 40);
	m_gameObjectManager.add("AI_0", opponent);

	GameBall* ball = new GameBall(this);
	ball->setPosition((m_screenWidth / 2),(m_screenHeight / 2) + 30);
	m_gameObjectManager.add("Ball_0", ball);

	m_gameState = Initialized;

	return true;
}

void Game::start()
{
	if (m_gameState != Initialized)
	{
		return;
	}

	sf::Clock timer;
	float deltaTime = 0.0f;

	m_gameState = ShowingSplash;
	timer.restart();
	while (!isExiting())
	{
		deltaTime = timer.restart().asSeconds();
		gameLoop(deltaTime);
	}

	m_window.close();
}

bool Game::isExiting() const
{
	return m_gameState == Exiting;
}

int Game::getScreenWidth() const
{
	return m_screenWidth;
}

int Game::getScreenHeight() const
{
	return m_screenHeight;
}

const GameObjectManager& Game::getGameObjectManager() const
{
	return m_gameObjectManager;
}

void Game::gameLoop(float deltaTime)
{
	switch(m_gameState)
	{
		case Playing:
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_gameState = Exiting;
				}
			}

			m_gameObjectManager.updateAll(deltaTime);
			
			// TODO: Why clear using SFML API and push/pop states?
			m_window.clear(sf::Color(0,0,0));
			m_window.pushGLStates();
			m_gameObjectManager.drawAll(m_window);
			m_window.popGLStates();
			m_window.display();

			break;
		}
		case ShowingMenu:
		{
			showMenu();
			break;
		}
		case ShowingSplash:
		{
			showSplash();
			break;
		}
		case Paused:
		case Exiting:
		case Initialized:
		case Uninitialized:
		default:
		{
			break;
		}
	}
}

void Game::showSplash()
{
	// Create splash screen and pass control to it
	SplashScreen splash;
	splash.show(m_window);

	m_gameState = ShowingMenu;
}

void Game::showMenu()
{
	MainMenu mainMenu;

	// In most cases this loop will roll only once, but why not? :D
	do
	{
		// Pass window control to MainMenu::show until it returns
		auto result = mainMenu.show(m_window);
		switch (result)
		{
			case MainMenu::Exit:
			{
				m_gameState = Exiting;
				return;
			}
			case MainMenu::Play:
			{
				m_gameState = Playing;
				return;
			}
			case MainMenu::Nothing:
			default:
			{
				continue;
			}
		}
	}
	while (true);
}
