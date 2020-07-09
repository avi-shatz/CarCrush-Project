#include <Data.h>
#include <State.h>
#include <EndState.h>
#include <Label.h>
#include <utilities.h>
#include <ResourceHolder.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


EndState::EndState(StateStack& stack, Context context)
	: State(stack, context)
	, m_GUIContainer()
	, m_showText(true)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	m_backgroundSprite.setTexture(texture);

	std::string str;
	
	if (Data::instance().hasWon())
	{
		str = "You Win !";
	}
	else
	{
		str = "You Loose !";
	}
	auto announcement = std::make_shared<GUI::Label>(str, *context.fonts);
	announcement->setPosition(500.f, 150.f);
	m_GUIContainer.pack(announcement);

	m_text.setFont(context.fonts->get(Fonts::Main));
	m_text.setString("Press enter to go back to menu");
	m_text.setScale(2.3f, 2.3f);
	centerOrigin(m_text);
	m_text.setPosition(sf::Vector2f(context.window->getSize() / 2u) + sf::Vector2f{ 0.f, +370.f });
}

void EndState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(m_backgroundSprite);
	window.draw(m_GUIContainer);

	if (m_showText)
		window.draw(m_text);
}

bool EndState::update(sf::Time dt)
{
	m_textEffectTime += dt;

	if (m_textEffectTime >= sf::seconds(0.5f))
	{
		m_showText = !m_showText;
		m_textEffectTime = sf::Time::Zero;
	}

	return true;
}

bool EndState::handleEvent(const sf::Event& event)
{
	m_GUIContainer.handleEvent(event);

	// If any key is pressed, trigger the next screen
	if ((event.type == sf::Event::KeyReleased)
		&& (event.key.code == sf::Keyboard::Return))
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return false;
}
