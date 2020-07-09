#include "Obj.h"


Obj::Obj(const sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

void Obj::draw(sf::RenderTarget& target) const
{
	target.draw(m_sprite);
}


sf::Vector2f Obj::getPosition() const
{
	return m_sprite.getPosition();
}

float Obj::getRotation() const
{
	return m_sprite.getRotation();
}

sf::Sprite& Obj::getSprite()
{
	return m_sprite;
}

void Obj::setRotation(float rotation)
{
	m_sprite.setRotation(rotation);
}

void Obj::setOrigin(sf::Vector2f origin)
{
	m_sprite.setOrigin(origin);
}

void Obj::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

void Obj::setColor(sf::Color color)
{
	m_sprite.setColor(color);
}
