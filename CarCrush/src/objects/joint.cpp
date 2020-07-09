#include "Joint.h"
#include <iostream>

const float JOINT_SIZE = 206.f;

Joint::Joint(const sf::Vector2f position, std::string directions)
	:Obj(position)
{
	sf::FloatRect rect(position, sf::Vector2f{ JOINT_SIZE, JOINT_SIZE });
	m_sprite.setTexture(TextureHolder::instance().get(Textures::ID::Pink));
	m_sprite.setTextureRect((sf::IntRect)rect);
	initDirVec(directions);
	initEnterVec(position);
	initExitVec(position);
}

Joint::~Joint()
{
}

/* this function calculates the rotation of the car in any point
	of the joint acording to enter point, direction and some car info.*/

float Joint::getRotationNeeded(int enterPoint, Dir direction, float startR,
	int exitPoint, sf::Vector2f currPos) const
{
	float destR = 0.f, currH = 0.f, destH = 1.f;

	auto enP = m_enterVec[enterPoint];
	auto exP = m_exitVec[exitPoint];
	

	switch (direction)
	{
	case Dir::Straight:
		return startR;
		break;
	case Dir::Right:
		destR = 90;
		break;
	case Dir::Left:
		destR = -90;
		break;
	case Dir::Uturn:
	{
		auto middleP = getMiddlePoint(enterPoint);
		
		if (!passedMiddlePoint(enterPoint, currPos))
		{
			exP = middleP;
		}
		else
		{
			enP = middleP;
			startR -= 90;
		}
		destR = -90;
	}
		break;
	default:
		break;

	}

	if (enterPoint == 0 || enterPoint == 2) // if car moving verticaly
	{
		currH = abs(currPos.y - enP.y);
		destH = abs(exP.y - enP.y);
	}
	else   // if car moving horizontaly
	{
		currH = abs(currPos.x - enP.x);
		destH = abs(exP.x - enP.x);
	}

	auto rot = startR + (currH / destH) * destR;
	if ((currH / destH) > 1.f)
		rot = startR + destR;

	return  rot;
}

Dir Joint::getRandomDirection() const
{
	Dir dir = m_dirVec[random_generator(0, m_dirVec.size() -1)];
	return dir;
	//return Dir::Straight;
}

int Joint::getEnterPoint(const sf::Vector2f position) const
{
	int index = 0;
	float dist = operation2f::distance(m_enterVec[0], position);

	for (int i = 1; i < m_enterVec.size(); i++)
	{
		float tempDist = operation2f::distance(m_enterVec[i], position);
		if (tempDist < dist) 
		{
			dist = tempDist;
			index = i;
		}
			
	}

	return index;
}

sf::Vector2f Joint::getCorrectPos(int enterPoint, sf::Vector2f position) const
{
	auto pos = position;
	if (enterPoint == 0 || enterPoint == 2) // if car moving verticaly
	{
		pos.x = m_enterVec[enterPoint].x;
	}
	else   // if car moving horizontaly
	{
		pos.y = m_enterVec[enterPoint].y;
	}
	return pos;
}

// dtermine exit point acording to enterPoint and direction.
int Joint::getExitPoint(int enterPoint, Dir direction) const
{
	int ep = enterPoint; // short name for enterPoint
	int exitPoint = 0; // exit point

	switch (direction)
	{
	case Dir::Straight:
	{
		std::vector<int> exVec{ 2, 3, 0, 1 };
		exitPoint = exVec[enterPoint];
	}
		break;
	case Dir::Right:
	{
		std::vector<int> exVec{ 3, 0, 1, 2 };
		exitPoint = exVec[enterPoint];
	}
		break;
	case Dir::Left:
	{
		std::vector<int> exVec{ 1, 2, 3, 0 };
		exitPoint = exVec[enterPoint];
	}
		break;
	case Dir::Uturn:
	{
		std::vector<int> exVec{ 0, 1, 2, 3 };
		exitPoint = exVec[enterPoint];
	}
		break;
	default:
		break;
	}

	return exitPoint;
}

void Joint::initDirVec(std::string directions)
{
	for(int i =0; i< directions.size(); i++)
	{
		char c = directions[i];
		switch (c)
		{
		case 'r':
			m_dirVec.push_back(Dir::Right);
			break;
		case 'l':
			m_dirVec.push_back(Dir::Left);
			break;
		case 's':
			m_dirVec.push_back(Dir::Straight);
			break;
		case 'u':
			m_dirVec.push_back(Dir::Uturn);
			break;
		default:
			throw std::logic_error("direction string has invalid letters");
			break;
		}
	}
}

void Joint::initEnterVec(const sf::Vector2f pos)
{
	m_enterVec.emplace_back(sf::Vector2f{pos.x + (3/4.f *JOINT_SIZE), pos.y + (1.f *JOINT_SIZE) });
	m_enterVec.emplace_back(sf::Vector2f{pos.x + (0.f *JOINT_SIZE), pos.y + (3/4.f *JOINT_SIZE) });
	m_enterVec.emplace_back(sf::Vector2f{pos.x + (1/4.f *JOINT_SIZE), pos.y + (0.f *JOINT_SIZE) });
	m_enterVec.emplace_back(sf::Vector2f{pos.x + (1.f *JOINT_SIZE), pos.y + (1/4.f *JOINT_SIZE) });
}

void Joint::initExitVec(const sf::Vector2f pos)
{
	m_exitVec.emplace_back(sf::Vector2f{ pos.x + (1/4.f * JOINT_SIZE), pos.y + (1.f * JOINT_SIZE) });
	m_exitVec.emplace_back(sf::Vector2f{ pos.x + (0.f * JOINT_SIZE), pos.y + (1/4.f * JOINT_SIZE) });
	m_exitVec.emplace_back(sf::Vector2f{ pos.x + (3/4.f * JOINT_SIZE), pos.y + (0.f * JOINT_SIZE) });
	m_exitVec.emplace_back(sf::Vector2f{ pos.x + (1.f * JOINT_SIZE), pos.y + (3/4.f * JOINT_SIZE) });
}

sf::Vector2f Joint::getMiddlePoint(int enterPoint) const
{
	sf::Vector2f middleP = getPosition();
	switch (enterPoint)
	{
	case 0:
		middleP += sf::Vector2f{JOINT_SIZE / 2.f, JOINT_SIZE * 6 / 10.f};
		break;
	case 1:
		middleP += sf::Vector2f{JOINT_SIZE * 4 / 10.f, JOINT_SIZE / 2.f};
		break;
	case 2:
		middleP += sf::Vector2f{JOINT_SIZE / 2.f, JOINT_SIZE * 4 / 10.f};
		break;
	case 3:
		middleP += sf::Vector2f{JOINT_SIZE * 6 / 10.f, JOINT_SIZE / 2.f};
		break;
	default:
		throw std::logic_error("enter point out of range");
		break;
	}

	return middleP;
}

bool Joint::passedMiddlePoint(int enterPoint, sf::Vector2f currPos) const
{
	auto middleP = getPosition() + sf::Vector2f{JOINT_SIZE, JOINT_SIZE}/2.f;

	switch (enterPoint)
	{
	case 0:
		return currPos.x < middleP.x;
	case 1:
		return currPos.y < middleP.y;
	case 2:
		return currPos.x > middleP.x;
	case 3:
		return currPos.y > middleP.y;
	default:
		throw std::logic_error("enter point out of range");
		break;
	}

	return false;
}
