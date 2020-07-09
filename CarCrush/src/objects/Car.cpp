#include "Car.h"
#include <cmath>
#include <iostream>
#include"SoundPlayer.h"

sf::Clock Car::timer{};

Car::Car(const sf::Vector2f position, float maxSpeed)
	:MovableObj(position)
	, m_prevR(0.f)
	, m_maxSpeed(maxSpeed)
	, m_type(Type::None)
{
	m_sprite.setTexture(TextureHolder::instance().get(Textures::ID::Car));
	m_sprite.setOrigin((1 / 2) * CAR_WIDTH, 10/10 * CAR_LENGTH);
	m_sprite.setPosition(position);
	m_sprite.setRotation(0);
	m_sprite.setColor(sf::Color::Blue);
}

void Car::move(const Directions& directions, float dt)
{
	m_prevR = m_sprite.getRotation();
	m_prevP = m_sprite.getPosition();
	m_sprite.rotate(determineRotation(directions, dt));

	determineSpeed(directions, dt);

	determineMovementVec();

	m_sprite.move(m_movementVec * m_speed * dt);
}

void Car::collideWithWall()
{
	if(m_type == Type::Player)
		SoundPlayer::instance().playCrash();
	moveBack();
	flipSpeed();
}

void Car::moveBack()
{
	m_sprite.setPosition(m_prevP);
	m_sprite.setRotation(m_prevR);
}

void Car::flipSpeed()
{
	m_speed = -m_speed / 2.5f;
}

void Car::setType(Type type)
{
	m_type = type;
}

Type Car::getType() const
{
	return m_type;
}

void Car::pause()
{
	m_pause = true;
	m_pauseTime = timer.getElapsedTime().asSeconds();
	m_speed = 0;
}

bool Car::isPaused()
{
	if(m_pause && timer.getElapsedTime().asSeconds() > m_pauseTime + 1.0f)
		m_pause = false;
	return m_pause;
}

float Car::determineRotation(const Directions& directions, float dt)
{
	float rot = 0;
	//set direction
	if (directions._left && m_speed)
	{
		rot = -m_rotateAmount;
	}

	if (directions._right && m_speed)
	{
		rot = m_rotateAmount;
	}

	return rot * dt;
}

void Car::determineSpeed(const Directions& directions, float dt)
{
	//set speed
	if (directions._up && m_speed < m_maxSpeed)
		m_speed += m_acc * dt;

	if (directions._down && m_speed > -m_maxSpeed)
		m_speed -= m_acc * dt;

	// deceleration amount 
	float  currentDec = m_dec;

	if (directions._stop) // activate car break. 
		currentDec *= 3.5;

	// if the player don't accelerate,
	//slow the car down naturaly until a complete stop.
	if (directions._stop ||
		(!directions._up && !directions._down))
	{
		if (m_speed > 0.f + currentDec)
			m_speed -= currentDec * dt;
		else if (m_speed < 0.f - currentDec)
			m_speed += currentDec * dt;
		else
			m_speed = 0.f;
	}
}

void Car::determineMovementVec()
{
	//rotate direction vector
	sf::Vector2f oldVec = m_movementVec;
	sf::Transform t;
	t.rotate(m_sprite.getRotation());
	m_movementVec = t.transformPoint(forwardVec);
	//calc the dot product so any rotation reduces the
	//current speed - gives the impression of wheel spin
	//when accelerating after a tight turn
	//m_speed *= operation2f::dot(oldVec, m_movementVec);
}
