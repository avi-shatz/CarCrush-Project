#pragma once
#include "Obj.h"

class Edible : public Obj
{
public:
	Edible(const sf::Vector2f position);
	~Edible() = 0 {};

	bool isEaten() const;
	void eat();

private:

	bool		m_eaten;
};

