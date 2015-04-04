#pragma once

#include <list>

class MainMenu
{
public:
	enum MenuResult
	{
		Nothing,
		Exit,
		Play
	};

	struct MenuItem
	{
		sf::Rect<int> rect;
		MenuResult action;
	};

	MenuResult Show(sf::RenderWindow& a_Window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& a_Window);
	MenuResult HandleClick(int a_x, int a_y);

	std::list<MenuItem> m_MenuItems;
};
