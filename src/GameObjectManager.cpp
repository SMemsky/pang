#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() :
	m_gameObjects()
{}

GameObjectManager::~GameObjectManager()
{
	std::for_each(m_gameObjects.begin(), m_gameObjects.end(),
		GameObjectDeallocator());
}

void GameObjectManager::add(const std::string& name, VisibleGameObject* gameObject)
{
	m_gameObjects.insert(
		std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::remove(const std::string& name)
{
	auto result = m_gameObjects.find(name);
	if(result != m_gameObjects.end())
	{
		delete result->second;
		m_gameObjects.erase(result);
	}
}

VisibleGameObject* GameObjectManager::get(const std::string& name) const
{
	auto result = m_gameObjects.find(name);
	if(result == m_gameObjects.end())
	{
		return nullptr;
	}

	return result->second;
}

unsigned GameObjectManager::getObjectCount() const
{
	return m_gameObjects.size();
}

void GameObjectManager::drawAll(sf::RenderWindow& window)
{
	auto end = m_gameObjects.end();
	for (auto it = m_gameObjects.begin(); it != end; ++it)
	{
		it->second->draw(window);
	}
}

void GameObjectManager::updateAll(float deltaTime)
{
	auto end = m_gameObjects.end();
	for (auto it = m_gameObjects.begin(); it != end; ++it)
	{
		it->second->update(deltaTime);
	}
}
