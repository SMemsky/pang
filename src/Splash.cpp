#include "Splash.h"

void SplashScreen::show(sf::RenderWindow& window)
{
	sf::Texture image;
	if (!image.loadFromFile("res/splash.png"))
	{
		return;
	}
	sf::Sprite sprite(image);

	window.draw(sprite);
	window.display();

	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::MouseButtonPressed ||
				event.type == sf::Event::Closed)
			{
				return;
			}
		}

		window.draw(sprite);
		window.display();
	}
}
