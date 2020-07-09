#pragma once
#include <SFML/Graphics.hpp>
#include "utilities.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class Obj
{
public:
	Obj(const sf::Vector2f position);
	virtual ~Obj() = 0 {};

	virtual void draw(sf::RenderTarget& target) const;

	virtual sf::Vector2f getPosition() const;
	virtual float getRotation() const;
	virtual sf::Sprite& getSprite();
	virtual void setRotation(float rotation);
	virtual void setOrigin(sf::Vector2f origin);
	virtual void setPosition(sf::Vector2f position);
	virtual void setColor(sf::Color color);

protected:
	sf::Sprite m_sprite;
};

