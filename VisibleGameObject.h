#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string a_Filename);
	virtual void Draw(sf::RenderWindow& a_Window);
	virtual void Update(float deltaTime);
	
	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;

	virtual bool IsLoaded() const;
	virtual sf::Rect<float> GetBoundingRect() const;

protected:
	sf::Sprite& GetSprite();
	
private:

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	std::string m_Filename;

	bool m_bLoaded;

};
