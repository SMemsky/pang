#pragma once

#include <map>
#include <string>
#include <utility>

#include "VisibleGameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void add(const std::string& name, VisibleGameObject* gameObject);
	void remove(const std::string& name);
	unsigned getObjectCount() const;
	VisibleGameObject* get(const std::string& name) const;

	void drawAll(sf::RenderWindow& window);
	void updateAll(float deltaTime);
private:
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject*>& p)
			const
		{
			delete p.second;
		}
	};
private:
	std::map<std::string, VisibleGameObject*> m_gameObjects;
};
