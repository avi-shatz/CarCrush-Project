#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Collision.h"
#include "CollisionHandling.h"
#include "Coin.h"
#include "GiftTime.h"

class Map
{
public:
	Map();
	~Map() = default;

	void loadFromFile(const std::string& fileName);
	void loadWalls(std::istringstream& iss);
	void loadJoints(std::istringstream& iss);
	void loadGifts(std::istringstream& iss);

	void update(float dt);
	void draw(sf::RenderTarget& target);
	void drawMiniMap(sf::RenderTarget& target);

	bool checkColisionWithWalls(Obj& obj);
	bool checkColisionWithJoints(Obj& obj);
	bool checkColisionWithEdible(Obj& obj);

	bool intersectWithJoint(Joint* joint, Obj* obj);
private:
	sf::Sprite m_mapImg;
	sf::Sprite m_seaImg;

	std::vector <std::unique_ptr<Edible>> m_edibleVec;
	std::vector<Wall> m_wallVec;
	std::vector<Joint> m_jointVec;
};


