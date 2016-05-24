#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject() :
	m_sprite(),
	m_texture(),
	m_filename(),
	m_isLoaded(false)
{}

VisibleGameObject::~VisibleGameObject()
{}

void VisibleGameObject::load(const std::string& filename)
{
	if (!m_texture.loadFromFile(filename))
	{
		m_filename = "";
		m_isLoaded = false;
	}
	else
	{
		m_filename = filename;
		m_sprite.setTexture(m_texture);
		m_isLoaded = true;
	}
}

void VisibleGameObject::draw(sf::RenderWindow& window)
{
	if (m_isLoaded)
	{
		window.draw(m_sprite);
	}
}

void VisibleGameObject::update(float deltaTime)
{}

void VisibleGameObject::setPosition(float x, float y)
{
	if (m_isLoaded)
	{
		m_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::setPosition(const sf::Vector2f& pos)
{
	if (m_isLoaded)
	{
		m_sprite.setPosition(pos);
	}
}

sf::Vector2f VisibleGameObject::getPosition() const
{
	if (m_isLoaded)
	{
		return m_sprite.getPosition();
	}

	return sf::Vector2f();
}

bool VisibleGameObject::isLoaded() const
{
	return m_isLoaded;
}

float VisibleGameObject::getHeight() const
{
	return m_sprite.getLocalBounds().height;
}

float VisibleGameObject::getWidth() const
{
	return m_sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::getBoundingRect() const
{
	return m_sprite.getGlobalBounds();
}
