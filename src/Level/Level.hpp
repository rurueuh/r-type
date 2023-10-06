#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "World.hpp"


class Level
{
public:
	Level() = default;
	virtual ~Level() = default;

	virtual void update(const float dt) = 0;
	
	// operator
	bool operator==(const Level& other) const { return this == &other; }
	ECS::World* getWorld(void) { return _world; };

protected:
	ECS::World* _world = ECS::World::CreateWorld();
};