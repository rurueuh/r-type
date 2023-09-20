#pragma once

#include <iostream>
#include <memory>	
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


class Image : public sf::Drawable
{
public:
	Image(std::string path, sf::Vector2f position = {0, 0}, sf::Vector2f size = {0,0}) : m_position(position), m_size(size)
	{
		sf::Texture &texture = TextureManager::getTexture(path);
		m_sprite.setTexture(texture);
		m_sprite.setPosition(m_position);
		if (m_size == sf::Vector2f(0, 0))
			m_size = sf::Vector2f((float) texture.getSize().x, (float) texture.getSize().y);
		m_sprite.setScale(m_size.x / m_sprite.getLocalBounds().width, m_size.y / m_sprite.getLocalBounds().height);
	}
	~Image() {};

	void setPosition(sf::Vector2f position)
	{
		m_position = position;
		m_sprite.setPosition(m_position);
	}

	void setSize(sf::Vector2f size)
	{
		m_size = size;
		m_sprite.setScale(m_size.x / m_sprite.getLocalBounds().width, m_size.y / m_sprite.getLocalBounds().height);
	}

	sf::Vector2f getPosition() const
	{
		return m_position;
	}

	sf::Vector2f getSize() const
	{
		return m_size;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const
	{
		target.draw(m_sprite);
	}
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_size;

};

