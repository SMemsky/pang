#include "MainMenu.h"

MainMenu::MainMenu() :
	m_menuItems()
{}

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window)
{
	sf::Texture image;
	if (!image.loadFromFile("res/mainmenu.png"))
	{
		return Nothing;
	}
	sf::Sprite sprite(image);

	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.rect.height = 235;
	playButton.action = Play;

	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023;
	exitButton.rect.height = 235;
	exitButton.action = Exit;

	m_menuItems.push_back(playButton);
	m_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				return handleClick(event.mouseButton.x, event.mouseButton.y);
			}
			else if (event.type == sf::Event::Closed)
			{
				return Exit;
			}
		}

		// Redraw menu sprite on every frame
		window.draw(sprite);
		window.display();
	}
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y) const
{
	for (auto item : m_menuItems)
	{
		auto rect = item.rect;
		int bx = rect.left;
		int by = rect.top;
		int ex = rect.width + bx;
		int ey = rect.height + by;

		if (bx < x &&
			by < y &&
			ex > x &&
			ey > y)
		{
			return item.action;
		}
	}

	return Nothing;
}
