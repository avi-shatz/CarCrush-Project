#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <Container.h>

#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>
#include <math.h>
#include <iomanip>

const float X_SPACE = 850;
const float Y_SPACE = 520;

const int TIME_GO_TO_END = 15;

//singelton class

class Data : sf::NonCopyable
{
public:
	static Data& instance();
	
	void update(float dt);

	void restartData(int timeLimit, int moneyLimit);
	void draw(sf::RenderTarget& target);
	void incScore(int score);
	void decScore(int dScore);
	void incLimiTime(int time);
	void incLevel(int num = 1);
	void decLimiTime(int dtime);
	int  getLevel();
	bool lostLevel() const;
	bool wonLevel() const;

	void won();
	bool hasWon();

private:
	Data();
	void checkTime();
	void initAllText();	
	void setPositionDetails(const sf::View& view);

private:
	int			m_score;
	int			m_time;
	int			m_timeLimit;
	int			m_moneyLimit;
	int			m_level = 1;
	bool		m_won = false;
	bool		m_doDec = true;
	float		m_mainTimer = 0.f;
	float		m_decTimer = 0.f;

	sf::Font&				m_font;
	sf::Text				m_scoreText;

	sf::Sprite				m_dollarSprite;

	sf::Text				m_timeText;
	sf::Sprite				m_clockSprite;

	sf::Sprite				m_timeOut;

	sf::RectangleShape		m_rectBbackground;

	GUI::Container			m_GUIContainer;
};

