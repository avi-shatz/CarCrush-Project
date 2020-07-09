#include <State.h>
#include <HelpState.h>
#include <Label.h>
#include <utilities.h>
#include <ResourceHolder.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Audio.hpp>


HelpState::HelpState(StateStack& stack, Context context)
	: State(stack, context)
	, m_text()
{
	sf::Texture& texture = context.textures->get(Textures::Help);
	m_backgroundSprite.setTexture(texture);
	m_backgroundSprite.setPosition(sf::Vector2f(context.window->getSize().x /2.f - 450.f, context.window->getSize().y /2.f - 300.f));
	m_backgroundSprite.setScale(3.8f,3.8f);


	std::string str;

	str = str + "+ Goal:\n\t\tCollect money at a given time.\n\n"
		+ "+ There are two types of gifts :\n"
		+ "\t\tmoney-gift, and time-gift.\n"
		+ "\t\tEach time-gift gives you plus 8 seconds.\n"
		+ "\t\tEach money-gift gives you 57 points.\n\n"
		+ "+ Collision with another vehicle or wall causes lost of money.\n\n"
		+ "\t\t\t\t\tGood luck, we hope you enjoy!";
	
	m_text.setFont(context.fonts->get(Fonts::Main));
	m_text.setString(str);
	m_text.setScale(1.2f, 1.2f);
	centerOrigin(m_text);
	m_text.setPosition(m_backgroundSprite.getPosition().x + 550.f , m_backgroundSprite.getPosition().y + 310.f);
}

void HelpState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(m_backgroundSprite);
	window.draw(m_text);
}

bool HelpState::update(sf::Time)
{
	return true;
}

bool HelpState::handleEvent(const sf::Event& event)
{
	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed)
	{		
		requestStackPop();
	}
		
  	return false;
}
