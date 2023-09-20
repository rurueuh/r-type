#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "GameInstance.h"
#include "TextureManager.h"
class Component;

typedef struct stats_s {
	int health		= 20;
	int maxHealth	= 20;
	int mana		= 100;
	int maxMana		= 100;
	int attack		= 1;
	int defense		= 1;
	int speed		= 1;
	int luck		= 1;

	stats_s() = default;

	bool operator==(const stats_s& other) const
	{
		return health == other.health && maxHealth == other.maxHealth && mana == other.mana && maxMana == other.maxMana && attack == other.attack && defense == other.defense && speed == other.speed && luck == other.luck;
	}
	bool operator!=(const stats_s& other) const
	{
		return !(*this == other);
	}
} stats_t;

enum Direction {
	Up = 0,
	Down,
	Left,
	Right
};

class Entity
{
public:
	// CONSTRUCTORS //
	Entity() {
		initStats();
	};
	Entity(sf::Vector2f position) : m_position(position) {
		m_sprite.setPosition(m_position);
		initStats();
	};
	Entity(sf::Vector2f position, sf::Vector2f size) : m_position(position), m_size(size) {
		m_sprite.setPosition(m_position);
		initStats();
	};
	virtual ~Entity() {};

	virtual void initStats() {};

	// for auto updating and drawing components
	void EntityUpdate(float dt);
	void EntityDraw(sf::RenderTarget& window);

	// update and draw functions for the entity
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget& window) = 0;

	// GETTERS AND SETTERS //
	sf::Vector2f getPosition() { return m_position; }
	void setPosition(sf::Vector2f position) { m_position = position; m_sprite.setPosition(position); }
	void move(sf::Vector2f offset) { m_position += offset; m_sprite.move(offset); }

	sf::Vector2f getSize() { return m_size; }
	void setSize(sf::Vector2f size) { m_size = size; }

	sf::Sprite &getSprite() { return m_sprite; }
	sf::Sprite *getSpritePtr() { return &m_sprite; }
	void setSprite(sf::Sprite sprite) { m_sprite = sprite; }

	stats_t& getStats() { return m_stats; }
	void setStats(stats_t stats) { m_stats = stats; }

	// OPERATORS //
	bool operator==(const Entity& other) const = default;

	// COMPONENTS //
	template <typename T>
	std::shared_ptr<T> getComponent()
	{
		for (auto& comp : _components)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(comp))
				return ptr;
		}
		return nullptr;
	}
	template <typename T>
	void addComponent(void)
	{
		std::shared_ptr<T> component = std::make_shared<T>(this);
		_components.push_back(component);
	}
	template <typename T>
	void removeComponent(void)
	{
		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(*it))
			{
				_components.erase(it);
				return;
			}
		}
	}

	protected:
		std::vector<std::shared_ptr<Component>> _components;
		sf::Vector2f m_position = sf::Vector2f(0, 0);
		sf::Vector2f m_size = sf::Vector2f(0, 0);
		sf::Texture m_texture;
		sf::Sprite m_sprite;

		stats_t m_stats;
};

