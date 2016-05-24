#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void load(const std::string& filename);
	virtual void draw(sf::RenderWindow& window);
	virtual void update(float deltaTime);
	
	virtual void setPosition(float x, float y);
	virtual void setPosition(const sf::Vector2f& pos);
	virtual sf::Vector2f getPosition() const;
	virtual float getWidth() const;
	virtual float getHeight() const;

	virtual bool isLoaded() const;
	virtual sf::Rect<float> getBoundingRect() const;
protected:
	sf::Sprite m_sprite;
private:
	sf::Texture m_texture;

	std::string m_filename;

	bool m_isLoaded;

};
