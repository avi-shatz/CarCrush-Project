#include "Driver.h"


Driver::Driver(const sf::Vector2f position)
	:Obj(position), m_car(nullptr)
{
}

void Driver::attachCar(Car* car)
{
	m_car = car;
}

void Driver::dettachCar()
{
	m_sprite.setPosition(m_car->getPosition());
	m_car->setType(Type::None);
	m_car = nullptr;
}

void Driver::draw(sf::RenderTarget& target) const
{
	if (!m_car)
		target.draw(m_sprite);
}

sf::Vector2f Driver::getPosition() const
{
	if (m_car)
		return m_car->getPosition();
	else
		return m_sprite.getPosition();
}

float Driver::getRotation() const
{

	if (m_car)
		return m_car->getRotation();
	else
		return m_sprite.getRotation();
}

sf::Sprite& Driver::getSprite()
{
	if (m_car)
		return m_car->getSprite();
	else
		return m_sprite;
}

void Driver::setRotation(float rotation)
{
	if (m_car)
		m_car->setRotation(rotation);
	else
		m_sprite.setRotation(rotation);
}

void Driver::setOrigin(sf::Vector2f origin)
{
	if (m_car)
		m_car->setOrigin(origin);
	else
		m_sprite.setOrigin(origin);
}

void Driver::setPosition(sf::Vector2f position)
{
	if (m_car)
		m_car->setPosition(position);
	else
		m_sprite.setPosition(position);
}

void Driver::setColor(sf::Color color)
{
	if (m_car)
		m_car->setColor(color);
	else
		m_sprite.setColor(color);
}

Car* Driver::getCar()
{
	return m_car;
}
