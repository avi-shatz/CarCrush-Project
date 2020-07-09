#pragma once
#include <random>
#include <vector>
#include <math.h>       
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <sstream>

// getting a true random number between min - max
size_t random_generator(size_t min, size_t max);

//------------------ currently the functions below are not in use---------------------
namespace operation2f
{
	//calculates distance between 2 vectors
	float distance(sf::Vector2f v1, sf::Vector2f v2);

	//Returns length of a given vector
	inline float length(const sf::Vector2f& source);

	//calculates dot product of 2 vectors
	inline float dot(const sf::Vector2f& lv, const sf::Vector2f& rv);

	//Returns a given vector with its length normalized to 1
	inline sf::Vector2f normalise(sf::Vector2f source);
}

//sfml book utilities
//=====================================================

namespace sf
{
	class Sprite;
	class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

template <typename T>
std::string toString(const T& value)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}