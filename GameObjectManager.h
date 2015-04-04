#pragma once

#include "VisibleGameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string a_Name, VisibleGameObject* a_GameObject);
	void Remove(std::string a_Name);
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string a_Name) const;

	void DrawAll(sf::RenderWindow& a_Window);
	void UpdateAll();
	
private:
	std::map<std::string, VisibleGameObject*> m_GameObjects;

	sf::Clock clock;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string,VisibleGameObject*>& p) const
		{
			delete p.second;
		}
	};
};
