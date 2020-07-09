#include "Coin.h"

Coin::Coin(const sf::Vector2f& position)
	: Edible(position)
{
	m_sprite.setTexture(TextureHolder::instance().get(Textures::Money));
	m_sprite.setScale(0.2f, 0.2f);
	centerOrigin(m_sprite);
}

Coin::~Coin()
{
}
