#include "RobotDriver.h"
#include <iostream>
#include "World.h"

RobotDriver::RobotDriver(const sf::Vector2f position, World& world)
	:Driver(position)
	, m_world(world)
{
}

RobotDriver::~RobotDriver()
{
}

void RobotDriver::update(float dt)
{
	if (m_car->isPaused())
		return;
	if (m_car)
	{
		if (m_insideJoint)
			rotateCar();

		Directions directions{false, false, false, false, false};
		directions._up = true;
		m_car->move(directions, dt);
	}
}

void RobotDriver::collideWithJoint(Joint& joint)
{
	if (m_insideJoint == &joint)
		return;

	if (m_world.jointOccupied(&joint, m_car))
	{
		m_car->moveBack();
		m_car->pause();
		return;
	}

	m_insideJoint = &joint;
	m_enterPoint = joint.getEnterPoint(getPosition());
	m_dir = joint.getRandomDirection();
	correctRotation();
	m_startRot = m_car->getRotation();
	m_car->setPosition(joint.getCorrectPos(m_enterPoint, getPosition()));	
	m_exitPoint = joint.getExitPoint(m_enterPoint, m_dir);
}

void RobotDriver::attachCar(Car* car)
{
	Driver::attachCar(car);
	car->setType(Type::Robot);
}

void RobotDriver::rotateCar()
{
	float rotation = m_insideJoint->getRotationNeeded
		(m_enterPoint, m_dir, m_startRot, m_exitPoint, getPosition());

	//std::cout << rotation << " | " << getPosition().x << " " << getPosition().y << "\n";
	m_car->setRotation(rotation);
}

void RobotDriver::correctRotation()
{
	auto r = int(abs(getRotation())) % 360;

	if (abs(r - abs(90)) < 30)
		r = 90;
	else if (abs(r - abs(180)) < 30)
		r = 180;
	else if (abs(r - abs(270)) < 30)
		r = 270;
	else if (abs(r - abs(0)) < 30)
		r = 0;

	setRotation(float(r));
}
