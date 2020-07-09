#pragma once

#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>
#include <Player.h>
#include <StateStack.h>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
public:
	Application();
	void run();


private:
	void processInput();
	void update(sf::Time dt);
	void render();

	void updateStatistics(sf::Time dt);
	void registerStates();


private:
	void loadResources();
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		m_window;
	TextureHolder&			m_textures;
	FontHolder&				m_fonts;
	
	StateStack				m_stateStack;

	sf::Text				m_statisticsText;
	sf::Time				m_statisticsUpdateTime;
	std::size_t				m_statisticsNumFrames;
};
