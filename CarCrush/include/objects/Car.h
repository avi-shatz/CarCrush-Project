#pragma once
#include "MovableObj.h"

constexpr auto CAR_WIDTH = 49;
constexpr auto CAR_LENGTH = 93;

enum class Type
{
	None,
	Robot,
	Player
};

class Car : public MovableObj
{
public: 
	Car(const sf::Vector2f position, float maxSpeed = 150.f);
	~Car() {};

	void move(const Directions& directions, float dt) override;
	void collideWithWall();
	void moveBack();
	void flipSpeed();
	void setType(Type type);
	Type getType() const;
	void pause();
	bool isPaused();

private:
	float determineRotation(const Directions& directions, float dt);
	void determineSpeed(const Directions& directions, float dt);
	void determineMovementVec();

	float			m_maxSpeed;
	const float		m_acc = 45.f;
	const float		m_dec = 25.f; //acceleration and deceleration
	const float		m_rotateAmount = 85.f ;

	float			m_prevR;
	sf::Vector2f	m_prevP;
	Type			m_type;

	float m_pauseTime = 0.f;
	bool m_pause = false;
	static sf::Clock timer;
};