#include <MenuState.h>
#include <Button.h>
#include <Label.h>

#include <utilities.h>
#include <ResourceHolder.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, m_GUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	m_backgroundSprite.setTexture(texture);

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition(100.f, 450.f);
	playButton->setScale(1.5f, 1.8f);	
	playButton->setText("Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto helpButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	helpButton->setPosition(100.f, 550.f);
	helpButton->setScale(1.5f, 1.8f);
	helpButton->setText("Help");
	helpButton->setCallback([this]()
		{
			requestStackPush(States::Help);
		});
	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(100.f, 650.f);
	exitButton->setScale(1.5f, 1.8f);
	exitButton->setText("Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	std::string str = "Developed by: Avigdor shatz, Nati Grossman.";
	auto credit = std::make_shared<GUI::Label>(str, *context.fonts, 50);
	credit->setPosition(270.f, 900.f);

	m_GUIContainer.pack(playButton);
	m_GUIContainer.pack(helpButton);
	m_GUIContainer.pack(exitButton);
	m_GUIContainer.pack(credit);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(m_backgroundSprite);
	window.draw(m_GUIContainer);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	m_GUIContainer.handleEvent(event);
	return false;
}
