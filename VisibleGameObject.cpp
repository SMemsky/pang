#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject() :
	m_bLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject()
{

}

void VisibleGameObject::Load(std::string a_Filename)
{
	if (!m_Texture.loadFromFile(a_Filename))
	{
		m_Filename = "";
		m_bLoaded = false;
	}
	else
	{
		m_Filename = a_Filename;
		m_Sprite.setTexture(m_Texture);
		m_bLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow& a_Window)
{
	if (m_bLoaded)
	{
		a_Window.draw(m_Sprite);
	}
}

void VisibleGameObject::Update(float deltaTime)
{

}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (m_bLoaded)
	{
		m_Sprite.setPosition(x, y);
	}
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (m_bLoaded)
	{
		return m_Sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return m_Sprite;
}

bool VisibleGameObject::IsLoaded() const
{
	return m_bLoaded;
}

float VisibleGameObject::GetHeight() const
{
	return m_Sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
	return m_Sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	return m_Sprite.getGlobalBounds(); //HELLOO
}
