#pragma once
#include "Obj.h"

enum class Dir
{
	Straight,
	Right,
	Left,
	Uturn,
};

class Joint : public Obj
{
public:
	Joint(const sf::Vector2f position, std::string directions = "s");
	~Joint();

	float getRotationNeeded(int enterPoint, Dir direction, float startR,
		int exitPoint, sf::Vector2f currPos) const;
	Dir getRandomDirection() const;
	int getEnterPoint(const sf::Vector2f position) const;
	sf::Vector2f getCorrectPos(int enterPoint, sf::Vector2f position) const;
	int getExitPoint(int enterPoint, Dir direction) const;

private:
	void initDirVec(std::string directions);
	void initEnterVec(const sf::Vector2f position);
	void initExitVec(const sf::Vector2f position);
	sf::Vector2f getMiddlePoint(int enterPoint) const;
	bool passedMiddlePoint(int enterPoint, sf::Vector2f currPos) const;

private:

	std::vector<Dir> m_dirVec;
	std::vector<sf::Vector2f> m_enterVec;
	std::vector<sf::Vector2f> m_exitVec;
}; 
