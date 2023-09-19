#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class Component;

class Entity
{
public:
	// CONSTRUCTORS //
	Entity() {};
	virtual ~Entity() {};

	// for auto updating and drawing components
	void EntityUpdate(float dt);
	void EntityDraw(sf::RenderTarget& window);

	// update and draw functions for the entity
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget& window) = 0;

	// GETTERS AND SETTERS //

	// OPERATORS //
	bool operator==(const Entity& other) const { return this == &other;}

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
	template <typename T, typename... Args>
	void addComponent(Args&&... args)
	{
		std::shared_ptr<T> component = std::make_shared<T>(this, std::forward<Args>(args)...);
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
};