#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"


class Component
{
	public:
	Component(Entity *entity, bool updatable = true, bool drawable = true) : _entity(entity), _updatable(updatable), _drawable(drawable) {};
	virtual ~Component() {};

	void CompenantUpdate(float dt) { if (_updatable) update(dt); }
	void CompenantDraw(sf::RenderTarget& window) { if (_drawable) draw(window); }

	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget& window) = 0;


	bool isUpdatable() const { return _updatable; }
	bool isDrawable() const { return _drawable; }

	void setUpdatable(bool updatable) { _updatable = updatable; }
	void setDrawable(bool drawable) { _drawable = drawable; }

	bool operator==(const Component& other) const = default;

protected:
	Entity* _entity;

private:
	bool _updatable;
	bool _drawable;

};

