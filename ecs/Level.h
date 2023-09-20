#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameInstance.h"
#include "TextureManager.h"
#include "Entity.h"
#include "Utils.h"

class Level
{
public:
	Level() = default;
	virtual ~Level() = default;

	void LevelUpdate(const float dt)
	{
		for (auto& entity : _entities)
		{
			entity->EntityUpdate(dt);
		}
		update(dt);
	}
	void LevelDraw(sf::RenderTarget& target)
	{
		for (auto& entity : _entities)
		{
			entity->EntityDraw(target);
		}
		draw(target);
	}

	virtual void update(const float dt) = 0;
	virtual void draw(sf::RenderTarget& target) = 0;

	template <typename T>
	void addEntity(void)
	{
		std::shared_ptr<T> entity = std::make_shared<T>();
		_entities.push_back(entity);
	}

	template <typename T>
	void removeEntity(void)
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(*it))
			{
				_entities.erase(it);
				return;
			}
		}
	}

	template <typename T>
	std::shared_ptr<T> getEntity()
	{
		for (auto& entity : _entities)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(entity))
			{
				return ptr;
			}
		}
		return nullptr;
	}


	// operator
	bool operator==(const Level& other) const = default;

	protected:
		std::vector<std::shared_ptr<Entity>> _entities;
};

