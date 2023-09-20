#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
class Player;

class PlayerClass
{
	PlayerClass(Player *self) : self(self) {};
	virtual ~PlayerClass() {};

	virtual void initStats() = 0;

	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget& window) = 0;

	virtual void attack() {};
	virtual void special() {};

	private:
		Player *self;

};

