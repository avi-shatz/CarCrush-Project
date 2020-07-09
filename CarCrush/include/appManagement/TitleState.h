#pragma once
#include <State.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			m_backgroundSprite;
	sf::Text			m_text;

	bool				m_showText;
	sf::Time			m_textEffectTime;
};
