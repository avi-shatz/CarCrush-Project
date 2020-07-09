#pragma once
#include "Obj.h"

const auto forwardVec = sf::Vector2f(0.f, 1.f);

struct Directions
{
	bool _up = false;
	bool _down = false;
	bool _right = false;
	bool _left = false;
	bool _stop = false;
};

class MovableObj : public Obj
{
public:
	MovableObj(const sf::Vector2f position);
	virtual ~MovableObj() =0 {};
	virtual void move(const Directions& directions, float dt) = 0;
	//void setSpeed(float speed);
protected:
	float m_speed = 0.f;
	sf::Vector2f m_movementVec;
};
