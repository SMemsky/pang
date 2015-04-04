#include <SFML/Graphics.hpp>
#include <list>

#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& a_Window)
{
	sf::Texture image;
	if (!image.loadFromFile("res/Mainmenu.png"))
	{

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

	m_MenuItems.push_back(playButton);
	m_MenuItems.push_back(exitButton);

	a_Window.draw(sprite);
	a_Window.display();

	return GetMenuResponse(a_Window);
}

MainMenu::MenuResult MainMenu::HandleClick(int a_x, int a_y)
{
	std::list<MenuItem>::iterator it;

	for (it = m_MenuItems.begin(); it != m_MenuItems.end(); it++)
	{
		sf::Rect<int> tmprect = (*it).rect;
		int x = tmprect.left;
		int y = tmprect.top;
		int ex= tmprect.width + x;
		int ey= tmprect.height + y;

		if (x < a_x && ex > a_x && y < a_y && ey > a_y)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& a_Window)
{
	sf::Event event;

	while (true)
	{
		while (a_Window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(event.mouseButton.x, event.mouseButton.y);
			}
			else if (event.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}
