#pragma once

#include <list>

#include <SFML/Graphics.hpp>

class MainMenu
{
public:
	enum MenuResult
	{
		Nothing,
		Exit,
		Play
	};

	MainMenu();

	MenuResult show(sf::RenderWindow& window);
private:
	struct MenuItem
	{
		sf::Rect<int> rect;
		MenuResult action;
	};
private:
	MenuResult handleClick(int x, int y) const;

	std::list<MenuItem> m_menuItems;
};
