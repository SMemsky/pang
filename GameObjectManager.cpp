#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	std::for_each(m_GameObjects.begin(), m_GameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string a_Name, VisibleGameObject* a_GameObject)
{
	m_GameObjects.insert(std::pair<std::string, VisibleGameObject*>(a_Name, a_GameObject));
}

void GameObjectManager::Remove(std::string a_Name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = m_GameObjects.find(a_Name);
	if(results != m_GameObjects.end())
	{
		delete results->second;
		m_GameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string a_Name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = m_GameObjects.find(a_Name);
	if(results == m_GameObjects.end())
	{
		return NULL;
	}

	return results->second;
}

int GameObjectManager::GetObjectCount() const
{
	return m_GameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& a_Window)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = m_GameObjects.begin();
	while(itr != m_GameObjects.end())
	{
		itr->second->Draw(a_Window);
		itr++;
	}
}

void GameObjectManager::UpdateAll()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = m_GameObjects.begin();
	float deltaTime = clock.restart().asSeconds();

	while(itr != m_GameObjects.end())
	{
		itr->second->Update(deltaTime);
		itr++;
	}
}
