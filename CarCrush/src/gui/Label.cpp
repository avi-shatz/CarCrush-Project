#include <Label.h>
#include "utilities.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Label::Label(const std::string& text, const FontHolder& fonts, int size)
: m_text(text, fonts.get(Fonts::Main), size)
{
}

bool Label::isSelectable() const
{
    return false;
}

void Label::handleEvent(const sf::Event&)
{
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_text, states);
}

void Label::setText(const std::string& text)
{
	m_text.setString(text);
}

}