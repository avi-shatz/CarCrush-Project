#include "Data.h"
#include <Label.h>
#include"SoundPlayer.h"

Data::Data()
: m_font(FontHolder::instance().get(Fonts::Main))
, m_GUIContainer()
{
	initAllText();
}

Data& Data::instance()
{
	static auto instance = Data();
	return instance;
}

void Data::update(float dt)
{
	m_mainTimer += dt;
}

void Data::restartData(int timeLimit, int moneyLimit)
{
	m_timeLimit = timeLimit;
	m_moneyLimit = moneyLimit;
	m_score = 0;
	m_doDec = true;
	m_mainTimer = 0.f;
}

void Data::initAllText()
{	
	m_rectBbackground.setSize({ 750,50 });
	m_rectBbackground.setFillColor(sf::Color(96, 96, 96));

	m_scoreText.setFont(m_font);
	m_scoreText.setString("");

	m_dollarSprite.setTexture(TextureHolder::instance().get(Textures::Dollar));
	m_dollarSprite.scale(1/13.f, 1/13.f);

	//init the time!
	m_clockSprite.setTexture(TextureHolder::instance().get(Textures::Clock));
	m_clockSprite.scale(0.1f, 0.1f);

	m_timeText.setFont(m_font);
	m_timeText.setString("");

	m_timeOut.setTexture(TextureHolder::instance().get(Textures::TimeOut));
	m_timeOut.setScale(2.2f, 2.2f);
	m_timeOut.setColor({ 255, 255, 255, 50 });
}

void Data::draw(sf::RenderTarget& target)
{
	/*m_GUIContainer.clear();
	auto text1 = std::make_shared<GUI::Label>(TXT_SCORE, FontHolder::instance(), 30);
	text1->setPosition(0, 0);
	m_GUIContainer.pack(text1);*/
	
	std::string str; 
	str = std::to_string(m_score) + "\\" + std::to_string(m_moneyLimit);
	m_scoreText.setString(str);


	const sf::View& view = target.getView();
	const sf::View& dView = target.getDefaultView();
	setPositionDetails(dView);
	target.setView(dView);
	
	target.draw(m_rectBbackground);
	target.draw(m_scoreText);
	target.draw(m_dollarSprite);

	checkTime();
	m_timeText.setString(std::to_string(m_time));
	target.draw(m_clockSprite);
	target.draw(m_timeText);
	//target.draw(m_GUIContainer);
	
	if (m_time < TIME_GO_TO_END)
	{
		if(m_time > 1)
			SoundPlayer::instance().playClockTic();
		auto clockPosi = sf::Vector2f{ view.getCenter().x - 520.f , view.getCenter().y - 520.f };
		m_timeOut.setPosition(clockPosi);
		if( m_time % 3 == 0 )
			target.draw(m_timeOut);
	}	
	target.setView(view);
}
void Data::setPositionDetails(const sf::View& view)
{
	auto lineDetails = sf::Vector2f{ view.getCenter().x - X_SPACE , view.getCenter().y - Y_SPACE };
	m_rectBbackground.setPosition(lineDetails);
	m_dollarSprite.setPosition(lineDetails.x + 50.f, lineDetails.y);
	m_scoreText.setPosition(lineDetails.x + 150.f, lineDetails.y + 5);
	m_clockSprite.setPosition(lineDetails.x + 600.f, lineDetails.y);
	m_timeText.setPosition(lineDetails.x + 665, lineDetails.y + 5);
}

void Data::checkTime()
{
	m_time = m_timeLimit - int(m_mainTimer);
}

bool Data::lostLevel() const
{
	return (m_time <= 0);
}

bool Data::wonLevel() const
{
	return (m_score >= m_moneyLimit);
}

void Data::won()
{
	m_won = true;
}

bool Data::hasWon()
{
	return m_won;
}

void Data::incScore(int score)
{
	m_score += score;
}

void Data::decScore(int dScore)
{
	if (!m_doDec)
	{
		if(m_mainTimer > m_decTimer+0.5f)
			m_doDec = true;
	}

	if (m_doDec)
	{
		m_score -= dScore;
		m_doDec = false;
		m_decTimer = m_mainTimer;
	}
		
}

void Data::incLimiTime(int time)
{
	m_timeLimit += time;
}

void Data::incLevel(int num)
{
	m_level += num;
}

void Data::decLimiTime(int dtime)
{
	m_timeLimit -= dtime;
}

int Data::getLevel()
{
	return m_level;
}




