#include "GiftTime.h"


GiftTime::GiftTime(const sf::Vector2f& position)
	:Edible(position)
{
	m_sprite.setTexture(TextureHolder::instance().get(Textures::Clock));
	m_sprite.setScale(0.19f, 0.19f);
	centerOrigin(m_sprite);
}

GiftTime::~GiftTime()
{
}