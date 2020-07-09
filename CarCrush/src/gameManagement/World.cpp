#pragma warning(push)
#pragma warning(disable:26812)  // turn off enum warnnings caused by sfml.

#include "World.h"
#include <fstream>
#include <sstream>
#include <string>

const auto MAP_SIZE = sf::Vector2f{4000.f, 3000.f};

const std::string ROBOTS_FILE = "robots.txt";

const sf::Vector2f PLAYER_INIT_POS = {2258, 1933};


World::World(sf::RenderWindow& window)
	:m_map(std::make_unique<Map>()), m_window(window)
{
	initWorld();
}

World::~World()
{
}

void World::initWorld()
{
	

	// create player
	m_driverVec.emplace_back(std::make_unique<Player>(PLAYER_INIT_POS));
	m_player = static_cast<Player*>(m_driverVec[0].get());

	// create player's car
	std::unique_ptr<Car> tempCar = std::make_unique<Car>(PLAYER_INIT_POS, 220.f);
	tempCar->setRotation(180);
	tempCar->setOrigin(sf::Vector2f{ (1 / 2.f) * CAR_WIDTH, 2 / 10.f * CAR_LENGTH });
	tempCar->setColor(sf::Color::Blue);
	m_carVec.push_back(std::move(tempCar));
	
	// create comp cars
	loadFromFile(ROBOTS_FILE);

	assert(m_driverVec.size() == m_carVec.size());
	
	//attach car to each player
	for (size_t i = 0; i < m_driverVec.size(); i++)
	{	
		m_driverVec[i]->attachCar(m_carVec[i].get());
	}
}

void World::loadFromFile(const std::string& fileName)
{
	std::fstream file(fileName);

	if (!file.is_open())
		throw std::runtime_error
		("couldn't open \"" + fileName + "\" ");

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);

		if (line.empty())
			continue;

		std::istringstream iss(line);

		if (fileName == ROBOTS_FILE)
			loadRobotsCars(iss);
		
	}
	file.close();
}

void World::loadRobotsCars(std::istringstream& iss)
{
	float xp, yp, rot;
	if (!(iss >> xp >> yp >> rot))
	{
		throw std::runtime_error
		(" \"" + ROBOTS_FILE + "\" has invalid input!");
	}

	std::unique_ptr<Car> tempCar = std::make_unique<Car>(sf::Vector2f{xp, yp});
	tempCar->setRotation(rot);
	tempCar->setOrigin(sf::Vector2f{ (1 / 2.f) * CAR_WIDTH, 10 / 10.f * CAR_LENGTH });
	tempCar->setColor(sf::Color::Yellow);
	m_carVec.push_back(std::move(tempCar));

	// create comp drivers
	m_driverVec.emplace_back(std::make_unique<RobotDriver>(sf::Vector2f{ xp, yp }, *this));
}

bool World::jointOccupied(Joint* joint, Car* car)
{
	for (auto& otherCar : m_carVec)
	{
		if (car != otherCar.get() &&
			m_map->intersectWithJoint(joint, otherCar.get()))
		{
			return true;
		}
	}
	return false;
}

void World::processEvents(const sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Z:
		m_zoomFactor *= 0.99f;
		break;
	case sf::Keyboard::Key::X:
		m_zoomFactor *= 1.01f;
		break;
	case sf::Keyboard::Key::M:
		m_showMiniMap = !m_showMiniMap;
		break;
	}
}

void World::update(float dt)
{
	for (auto& driver : m_driverVec)
	{
		driver->update(dt);
		Car* car = driver->getCar();
		if (car)
		{
			for (auto& otherCar : m_carVec)
				if (car != otherCar.get())
				{
					if (Collision::BoundingBoxTest(car->getSprite(), otherCar->getSprite()))
					{
						processCollision(*car, *otherCar);
						break;
					}
				}
		}
	}

	// handle colision of robots and joints
	for (auto& driver : m_driverVec)
	{
		if(driver.get() != m_player)
			m_map->checkColisionWithJoints(*driver);
	}

	for (auto& car : m_carVec)
	{
		m_map->checkColisionWithWalls(*car);
	}

	m_map->checkColisionWithEdible(*m_player);
	m_map->update(dt);
}

void World::draw() const
{
	sf::View view = m_window.getDefaultView();
	view.zoom(m_zoomFactor);
	view.setCenter(m_player->getPosition());
	
	m_window.setView(view);
	m_map->draw(m_window);

	for (auto& driver : m_driverVec)
	{
		driver->draw(m_window);
	}

	for (auto& car : m_carVec)
	{
		car->draw(m_window);
	}
	if(m_showMiniMap)
		drawMiniMap(m_window);
}


void World::drawMiniMap(sf::RenderTarget& target) const
{
	const sf::View& view = target.getView();
	sf::View miniView{ MAP_SIZE/2.f, MAP_SIZE };
	auto rect = sf::FloatRect{ 0.65f, 0.f, 0.35f, 0.45f };
	miniView.setViewport(rect);

	target.setView(miniView);
	m_map->drawMiniMap(m_window);
	m_player->getCar()->draw(m_window);

	sf::RectangleShape frame(miniView.getSize() - sf::Vector2f(60.f, 60.f));
	frame.setPosition(miniView.getCenter() - frame.getSize() / 2.f);
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(sf::Color::Yellow);
	frame.setOutlineThickness(60);
	target.draw(frame);

	target.setView(view);
}


#pragma warning(pop)
