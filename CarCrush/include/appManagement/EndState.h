#pragma once

#include <State.h>
#include <Container.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class EndState : public State
{
public:
	EndState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);
	

private:
	sf::Sprite				m_backgroundSprite;
	GUI::Container			m_GUIContainer;

	sf::Text			m_text;
	bool				m_showText;
	sf::Time			m_textEffectTime;
};
