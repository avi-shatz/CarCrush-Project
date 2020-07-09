#include "Wall.h"

Wall::Wall(const sf::Vector2f position, const sf::Vector2f size)
	:Obj(position)
{
	m_sprite = CreateRect(position, size);
}

Wall::~Wall()
{
}


sf::Sprite Wall::CreateRect(sf::Vector2f position, sf::Vector2f size)
{
	sf::FloatRect rect(position, size);
	sf::Sprite spriteShape;

	
	// set pink texture for debugging purposes
	sf::Texture& texture = TextureHolder::instance().get(Textures::ID::Pink);
	texture.setRepeated(true);

	spriteShape.setTexture(texture);
	spriteShape.setTextureRect((sf::IntRect)rect);
	spriteShape.setPosition(position);

	return std::move(spriteShape);
}