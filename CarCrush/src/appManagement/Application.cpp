#include <Application.h>
#include <State.h>
#include <StateIdentifiers.h>
#include <TitleState.h>
#include <GameState.h>
#include <MenuState.h>
#include <PauseState.h>
#include <EndState.h>
#include <HelpState.h>

const auto WIN_WIDTH = sf::VideoMode::getDesktopMode().width;
const auto WIN_LENGTH = sf::VideoMode::getDesktopMode().height;

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: m_window(sf::VideoMode(WIN_WIDTH, WIN_LENGTH), "GTA game", sf::Style::Close)
, m_textures(TextureHolder::instance())
, m_fonts(FontHolder::instance())
, m_stateStack(State::Context(m_window, m_textures, m_fonts))
, m_statisticsText()
, m_statisticsUpdateTime()
, m_statisticsNumFrames(0)
{
	m_window.setKeyRepeatEnabled(false);

	loadResources();

	m_statisticsText.setFont(m_fonts.get(Fonts::Main));
	m_statisticsText.setPosition(5.f, 5.f);
	m_statisticsText.setCharacterSize(10u);

	registerStates();
	m_stateStack.pushState(States::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (m_stateStack.isEmpty())
				m_window.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		m_stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Application::update(sf::Time dt)
{
	m_stateStack.update(dt);
}

void Application::render()
{
	m_window.clear();

	m_stateStack.draw();

	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_statisticsText);  

	m_window.display();
}

void Application::updateStatistics(sf::Time dt)
{
	m_statisticsUpdateTime += dt;
	m_statisticsNumFrames += 1;
	if (m_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		m_statisticsText.setString("FPS: " + toString(m_statisticsNumFrames));

		m_statisticsUpdateTime -= sf::seconds(1.0f);
		m_statisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	m_stateStack.registerState<TitleState>(States::Title);
	m_stateStack.registerState<MenuState>(States::Menu);
	m_stateStack.registerState<GameState>(States::Game);
	m_stateStack.registerState<PauseState>(States::Pause);
	m_stateStack.registerState<EndState>(States::End);
	m_stateStack.registerState<HelpState>(States::Help);
}

void Application::loadResources()
{
	m_fonts.load(Fonts::Main, "Sansation.ttf");
	//m_fonts.load(Fonts::Main, 	"ARIAL.TTF");

	m_textures.load(Textures::TitleScreen, "TitleScreen.jpg");
	m_textures.load(Textures::ButtonNormal, "ButtonNormal.png");
	m_textures.load(Textures::ButtonSelected, "ButtonSelected.png");
	m_textures.load(Textures::ButtonPressed, "ButtonPressed.png");

	m_textures.load(Textures::Background, "map1.png");
	m_textures.load(Textures::Sea, "sea.png");
	m_textures.load(Textures::Pink, "pinkRect.png");
	m_textures.load(Textures::Car, "RedCarImg.png");
	m_textures.load(Textures::Clock, "clock.png");
	m_textures.load(Textures::TimeOut, "time_out.png");
	m_textures.load(Textures::Money, "money.png");
	m_textures.load(Textures::Dollar, "dollar.png");
	m_textures.load(Textures::Help, "help.jpg");

	SoundHolder::instance().load(Sounds::Collision, "Smashed_Window_02.wav");
	SoundHolder::instance().load(Sounds::Pickup, "pickup_sound.ogg");
	SoundHolder::instance().load(Sounds::ClocKTic, "Clock_Ticking_D.wav");
}
