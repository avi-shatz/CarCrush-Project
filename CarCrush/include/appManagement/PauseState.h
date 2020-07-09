#pragma once

#include <State.h>
#include <Container.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
	public:
							PauseState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::Sprite			m_backgroundSprite;
		sf::Text			m_pausedText;
		GUI::Container 		m_GUIContainer;
};
