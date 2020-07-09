#pragma once


#include <Component.h>
#include <ResourceIdentifiers.h>
#include <ResourceHolder.h>

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

	class Label : public Component
	{
	public:
		typedef std::shared_ptr<Label> Ptr;


	public:
		Label(const std::string& text, const FontHolder& fonts, int size = 200);

		virtual bool		isSelectable() const;
		void				setText(const std::string& text);

		virtual void		handleEvent(const sf::Event& event);


	private:
		void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Text			m_text;
	};

}
