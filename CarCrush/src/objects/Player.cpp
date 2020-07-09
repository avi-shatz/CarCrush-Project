#pragma warning(push)
#pragma warning(disable:26812)  // turn off enum warnnings caused by sfml.
#include "Player.h"


constexpr auto CAR_LOCATION_Y = 380;
constexpr auto CAR_LOCATION_X = 380;

Player::Player(const sf::Vector2f position)
	: Driver(position)
{
}

void Player::processEvents(const sf::Keyboard::Key key)
{

}

void Player::update(float dt)
{
	if (m_car)
	{
		Directions directions; //  struct of 'false' initialized directions for car movement

		// setting directions according to player inputs.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			directions._up = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			directions._right = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			directions._down = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			directions._left = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			directions._stop = true;

		m_car->move(directions, dt);
	}
}

void Player::attachCar(Car* car)
{
	Driver::attachCar(car);
	car->setType(Type::Player);
}


#pragma warning(pop)
