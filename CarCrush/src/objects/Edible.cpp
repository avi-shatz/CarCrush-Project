#pragma once
#include "Edible.h"
#include"SoundPlayer.h"


Edible::Edible(const sf::Vector2f position)
	: Obj(position), m_eaten(false)
{

}

bool Edible::isEaten() const
{
	return m_eaten;
}

void Edible::eat()
{
	m_eaten = true;
	SoundPlayer::instance().playPickup();
}
