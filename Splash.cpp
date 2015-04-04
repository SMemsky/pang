#include <SFML/Graphics.hpp>

#include "Splash.h"

SplashScreen::SplashScreen()
{

}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::Show(sf::RenderWindow& a_Window)
{
	sf::Texture image;
	if (!image.loadFromFile("res/Splashscreen.png"))
	{
		return;
	}

	sf::Sprite sprite(image);

	a_Window.draw(sprite);
	a_Window.display();

	sf::Event event;

	while (true)
	{
		while (a_Window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed
				|| event.type == sf::Event::MouseButtonPressed
				|| event.type == sf::Event::Closed )
			{
				return;
			}
		}
	}
}
