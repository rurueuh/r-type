#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Level
{
public:
	Level() = default;
	virtual ~Level() = default;

	/// @brief update all entities of the level and the level
	/// @param dt 
	void LevelUpdate(const float dt)
	{
		for (auto& entity : _entities)
		{
			entity->EntityUpdate(dt);
		}
		update(dt);
	}
	/// @brief draw all entities of the level and the level
	/// @param target 
	void LevelDraw(sf::RenderTarget& target)
	{
		for (auto& entity : _entities)
		{
			entity->EntityDraw(target);
		}
		draw(target);
	}

	/// @brief update the level
	/// @param dt 
	virtual void update(const float dt) = 0;
	/// @brief draw the level
	/// @param target 
	virtual void draw(sf::RenderTarget& target) = 0;

	/// @brief create a new entity
	/// @tparam T 
	/// @example addEntity<Player>();
	/// @param  
	template <typename T>
	void addEntity(void)
	{
		_idEntity++;
		std::shared_ptr<T> entity = std::make_shared<T>();
		entity->setId(_idEntity);
		_entities.push_back(entity);
	}

	/// @brief remove all entities of a specific type
	/// @tparam T 
	/// @example removeEntity<Player>();
	/// @param  
	template <typename T>
	void removeEntity(void)
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(*it))
			{
				_entities.erase(it);
			}
		}
	}

	/// @brief remove the entity with the id
	/// @param id
	/// @example removeEntity(1);
	void removeEntity(const size_t id)
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
		{
			if ((*it)->getId() == id)
			{
				_entities.erase(it);
			}
		}
	}

	/// @brief remove the entity with the class
	/// @tparam T
	/// @example removeEntity(entity);
	void removeEntity(const Entity& entity)
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
		{
			if ((*it)->getId() == entity.getId())
			{
				_entities.erase(it);
			}
		}
	}	

	/// @brief get all entities of a specific type
	/// @tparam T herited class of Entity
	/// @example std::vector<std::shared_ptr<Enemy>> enemies = getEntity<Enemy>();
	/// @return std::vector<std::shared_ptr<T>>
	template <typename T>
	std::vector<std::shared_ptr<T>> getEntity()
	{
		std::vector<std::shared_ptr<T>> entities;
		for (auto& entity : _entities)
		{
			if (std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(entity))
			{
				entities.push_back(ptr);
			}
		}
		return entities;
	}

	/// @brief Get all entities load in the level
	/// @return 
	std::vector<std::shared_ptr<Entity>> getEntities() const { return _entities; }

	// operator
	bool operator==(const Level& other) const { return this == &other; }

	protected:
		size_t _idEntity = 0;
		std::vector<std::shared_ptr<Entity>> _entities;
};