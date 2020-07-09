#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		Background,
		Car,
		Sea,
		Pink,
		Clock,
		Dollar,
		Help,
		TimeOut,
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
		Money
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

namespace Sounds
{
	enum ID
	{
		Collision,
		Pickup,
		ClocKTic
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID>	    SoundHolder;

