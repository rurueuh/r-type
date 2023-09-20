#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


class TextButton : public sf::Drawable
{
	public:
		TextButton(std::string text, int policeSize, std::string fontPath, sf::Vector2f size = { 0, 0 }, sf::Vector2f position = { 0, 0 }, bool center = false) : m_position(position), m_size(size), m_center(center)
		{
			sf::Texture &texture = TextureManager::getTexture(m_buttonPath);
			background.setTexture(texture);
			background.setTextureRect(m_buttonRect);
			background.setPosition(m_position);
			if (m_size == sf::Vector2f(0, 0))
				m_size = sf::Vector2f((float)m_buttonRect.width, (float)m_buttonRect.height);
			background.setScale(m_size.x / m_buttonRect.width, m_size.y / m_buttonRect.height);
			m_font.loadFromFile(fontPath);
			m_text.setFont(m_font);
			m_text.setString(text);
			m_text.setCharacterSize(policeSize);
			m_text.setFillColor(sf::Color::White);
			m_text.setPosition(m_position);
			if (m_center)
			{
				m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height);
				m_text.setPosition(m_position.x + (m_size.x / 2), m_position.y + (m_size.y / 2));
			}
		}
		~TextButton() {};

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const
		{
			target.draw(background);
			target.draw(m_text);
		}

		void update(void)
		{
			if (isHover())
				background.setTextureRect(m_buttonRectHover);
			else
				background.setTextureRect(m_buttonRect);

		}
		bool isHover(void)
		{
			auto mousePos = sf::Mouse::getPosition();
			if (mousePos.x > m_position.x && mousePos.x < m_position.x + m_size.x && mousePos.y > m_position.y && mousePos.y < m_position.y + m_size.y)
				return true;
			return false;
		}
	private:
		sf::Font m_font;
		sf::Text m_text;

		sf::Sprite background;

		sf::Vector2f m_position;
		sf::Vector2f m_size;
		bool m_center;

		const sf::IntRect m_buttonRect = { 625, 31, 347, 51 };
		const sf::IntRect m_buttonRectHover = { 625, 100, 347, 51 };
		const std::string m_buttonPath = "assets/ui.png"; // TODO: change this to global const variable
};