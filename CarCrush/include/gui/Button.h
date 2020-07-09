#pragma once

#include <Component.h>
#include <ResourceIdentifiers.h>
#include <ResourceHolder.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GUI
{

	class Button : public Component
	{
	public:
		typedef std::shared_ptr<Button>		Ptr;
		typedef std::function<void()>		Callback;


	public:
		Button(const FontHolder& fonts, const TextureHolder& textures);

		void					setCallback(Callback callback);
		void					setText(const std::string& text);
		void					setToggle(bool flag);

		virtual bool			isSelectable() const;
		virtual void			select();
		virtual void			deselect();

		virtual void			activate();
		virtual void			deactivate();

		virtual void			handleEvent(const sf::Event& event);


	private:
		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		Callback				m_callback;
		const sf::Texture&		m_normalTexture;
		const sf::Texture&		m_selectedTexture;
		const sf::Texture&		m_pressedTexture;
		sf::Sprite				m_sprite;
		sf::Text				m_text;
		bool					m_isToggle;
	};

}
