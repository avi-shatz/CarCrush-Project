#include "Map.h"
#include <fstream>
#include <sstream>
#include <string>
#include <experimental/vector>


const std::string RECTANGLES_FILE = "rects.txt";
const std::string JOINTS_FILE = "joints.txt";
const std::string GIFTS_FILE = "gifts.txt";

const char COIN = 'c';
const char TIME = 't';

Map::Map()
{
	loadFromFile(RECTANGLES_FILE);
	loadFromFile(JOINTS_FILE);
	loadFromFile(GIFTS_FILE);

	// create background
	m_seaImg.setTexture( TextureHolder::instance().get(Textures::ID::Sea));
	m_seaImg.scale(3.5f, 5.f);
	m_seaImg.setPosition(-1000.f, -1000.f);

	//create map Texture
	m_mapImg.setTexture(TextureHolder::instance().get(Textures::ID::Background));
}


void Map::loadFromFile(const std::string& fileName)
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

		if (fileName == RECTANGLES_FILE)
			loadWalls(iss);
		else if (fileName == JOINTS_FILE)
			loadJoints(iss);
		else if (fileName == GIFTS_FILE)
			loadGifts(iss);
		else
			throw std::runtime_error
			("there is not a valid load function for this file");
	}
	file.close();
}

void Map::loadWalls(std::istringstream& iss)
{
	float xp, yp, xs, ys;
	if (!(iss >> xp >> yp >> xs >> ys))
	{
		throw std::runtime_error
		(" \"" + RECTANGLES_FILE + "\" has invalid input!");
	}

	m_wallVec.emplace_back(sf::Vector2f{ xp, yp }, sf::Vector2f{ xs, ys });
}

void Map::loadJoints(std::istringstream& iss)
{
	std::string directions;
	float xp, yp;
	if (!(iss >> xp >> yp >> directions))
	{
		throw std::runtime_error
		(" \"" + JOINTS_FILE + "\" has invalid input!");
	}

	m_jointVec.emplace_back(sf::Vector2f{ xp, yp }, directions);
}

void Map::loadGifts(std::istringstream& iss)
{
	char c;
	float xp, yp;
	if (!(iss >> c >> xp >> yp))
	{
		throw std::runtime_error
		(" \"" + GIFTS_FILE + "\" has invalid input!");
	}

	switch (c)
	{
	case COIN:
		m_edibleVec.emplace_back(std::make_unique<Coin>(sf::Vector2f{ xp, yp }));
		break;
	case TIME:
		m_edibleVec.emplace_back(std::make_unique<GiftTime>(sf::Vector2f{ xp, yp }));
		break;
	}
}

void Map::update(float dt)
{
	std::experimental::erase_if(m_edibleVec, [](const auto& edible)
		{ return edible->isEaten(); });
}

void Map::draw(sf::RenderTarget& target)
{
	target.draw(m_seaImg);
	target.draw(m_mapImg);

	for (const auto& edible : m_edibleVec)
		edible->draw(target);

	////for debug
	//for (const auto& wall : m_wallVec)
	//	wall.draw(target);
	
	//for debug
	//for (const auto& joint : m_jointVec)
	//	joint.draw(target);
}

void Map::drawMiniMap(sf::RenderTarget& target)
{
	target.draw(m_mapImg);

	for (const auto& edible : m_edibleVec)
		edible->draw(target);
}

bool Map::checkColisionWithWalls(Obj& obj)
{
	for (auto& wall : m_wallVec)
		if (Collision::BoundingBoxTest(wall.getSprite(), obj.getSprite()))
		{
			processCollision(obj, wall);
			return true;
		}
	return false;
}

bool Map::checkColisionWithJoints(Obj& obj)
{
	for (auto& joint : m_jointVec)
		if (Collision::BoundingBoxTest(joint.getSprite(), obj.getSprite()))
		{
			processCollision(obj, joint);
			return true;
		}
	return false;
}
bool Map::checkColisionWithEdible(Obj& obj)
{
	for (auto& edible : m_edibleVec)
		if (Collision::BoundingBoxTest(edible->getSprite(), obj.getSprite()))
		{
			processCollision(obj, dynamic_cast<Obj&>(*edible));
			return true;
		}

	return false;
}

bool Map::intersectWithJoint(Joint* joint, Obj* obj)
{
	return Collision::BoundingBoxTest
		(joint->getSprite(), obj->getSprite());
}

