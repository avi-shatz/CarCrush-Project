#include "Point.h"


Point::Point(const sf::Vector2f& position)
	: m_point(POINT_SIZE)
{
	m_point.setOrigin(m_point.getRadius(), m_point.getRadius());
	m_point.setPosition(position);
	m_point.setFillColor(POINT_COLOR);
}

void Point::draw(sf::RenderTarget& target) const
{
	target.draw(m_point);
}

Point::~Point()
{
}