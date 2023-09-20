#pragma once
#include "Entity.h"
#include "AnimationComponent.h"
#include "ControllerMouvement.h"

class Player :
    public Entity
{
    public:
		Player();
		~Player();

		void update(float dt) override;
		void draw(sf::RenderTarget& window) override;

		void initAnimations();
	private:
};

