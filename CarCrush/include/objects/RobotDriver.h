#pragma once
#include "Driver.h"
#include "Joint.h"
class World;

class RobotDriver :public Driver
{
public:
	RobotDriver(const sf::Vector2f position, World& world);
	~RobotDriver();

	virtual void update(float dt) override;
	void collideWithJoint(Joint& joint);
	virtual void attachCar(Car* car) override;

private:
	void rotateCar();
	void correctRotation();

private:
	Joint* m_insideJoint = nullptr;

	int m_enterPoint = 0;
	int m_exitPoint = 0;
	Dir m_dir = Dir::Straight;
	float m_startRot = 0.f;
	World& m_world;
};
