#pragma once

#include "Map.h"
#include "Player.h"
#include "Car.h"
#include "RobotDriver.h"

class World
{
public:
	World(sf::RenderWindow& window);
	~World();

	void processEvents(const sf::Keyboard::Key key);
	void update(float dt);
	void draw() const;
	bool jointOccupied(Joint* joint, Car* car);

private:

	void initWorld();
	void loadFromFile(const std::string& fileName);
	void loadRobotsCars(std::istringstream& iss);

private:
	void drawMiniMap(sf::RenderTarget& target)const;


	std::unique_ptr<Map>					m_map;
	std::vector< std::unique_ptr<Car>>		m_carVec;
	std::vector< std::unique_ptr<Driver>>	m_driverVec;

	Player*				m_player = nullptr; 
	float				m_zoomFactor = 0.8f;
	sf::RenderWindow&	m_window;
	bool m_showMiniMap = false;
};
