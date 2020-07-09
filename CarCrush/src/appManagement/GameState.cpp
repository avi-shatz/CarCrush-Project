#include <GameState.h>

const int LEVELS = 1;
const int LEVEL_TIME = 60;
const int LEVEL_MONEY = 250;

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, m_world(std::make_unique<World>(*context.window))
, m_data(Data::instance())
{
	m_data.restartData(LEVEL_TIME, LEVEL_MONEY);
}

void GameState::draw()
{
	m_world->draw();
	m_data.draw(*getContext().window);
}

bool GameState::update(sf::Time dt)
{
	m_world->update(dt.asSeconds());
	Data::instance().update(dt.asSeconds());

	if (m_data.lostLevel())
	{
		m_data.restartData(LEVEL_TIME, LEVEL_MONEY * m_data.getLevel());
		m_world = std::make_unique<World>(*getContext().window);
	}
	if (m_data.wonLevel())
	{
		m_data.incLevel();
		if (m_data.getLevel() > LEVELS)
		{
			m_data.won();
			requestStackPop();
			requestStackPush(States::Menu);
			requestStackPush(States::End);
		}

		m_data.restartData(LEVEL_TIME, LEVEL_MONEY * m_data.getLevel());
	}

	
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			requestStackPush(States::Pause);
		else
			m_world->processEvents(event.key.code);
	}
	return true;
}