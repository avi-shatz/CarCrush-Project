#pragma once
#include "Obj.h"

class Wall : public Obj
{
public:
	Wall(const sf::Vector2f position, const sf::Vector2f size);
	~Wall();

private:
	sf::Sprite CreateRect(sf::Vector2f position, sf::Vector2f size);
};
