#include "ControllerMouvement.h"
#include "AnimationComponent.h"

void ControllerMouvement::update(float dt)
{
	const float dtTime = this->_clock.getElapsedTime().asSeconds();
	if (dtTime < this->_timeUpdate)
	{
		return;
	}
	this->_clock.restart();

	auto animation = this->_entity->getComponent<AnimationComponent>();
	if (animation == nullptr) {
		static bool error = false;
		if (error)
			std::cerr << "ControllerMouvement::update: AnimationComponent is null" << std::endl;
		error = true;
		return;
	}

	sf::Vector2f velocityToAdd = { 0, 0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->_direction = Direction::Up;
		velocityToAdd.y += -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->_direction = Direction::Down;
		velocityToAdd.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		this->_direction = Direction::Left;
		velocityToAdd.x += -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->_direction = Direction::Right;
		velocityToAdd.x += 1;
	}

	if (velocityToAdd.x != 0 || velocityToAdd.y != 0)
	{
		if (velocityToAdd.x != 0) {
			this->_velocity.x = velocityToAdd.x * this->_acceleration;
		}
		if (velocityToAdd.y != 0) {
			this->_velocity.y = velocityToAdd.y * this->_acceleration;
		}
	}
	if (this->_velocity.x != 0 && velocityToAdd.x == 0) {
		this->_velocity.x -= this->_deceleration;
		if (this->_velocity.x < 0) {
			this->_velocity.x = 0;
		}
	}
	if (this->_velocity.y != 0 && velocityToAdd.y == 0) {
		this->_velocity.y -= this->_deceleration;
		if (this->_velocity.y < 0) {
			this->_velocity.y = 0;
		}
	}
	if (this->_velocity.x != 0 || this->_velocity.y != 0)
	{
		this->_isMoving = true;
		if (_direction == Direction::Up) {
			animation->playAnimation("walkBack", true);
		}
		else if (_direction == Direction::Down) {
			animation->playAnimation("walk", true);
		}
		else if (_direction == Direction::Left) {
			animation->playAnimation("walkLeft", true);
		}
		else if (_direction == Direction::Right) {
			animation->playAnimation("walkRight", true);
		}
	} else {
		this->_isMoving = false;
		if (_direction == Direction::Up) {
			animation->playAnimation("idleBack", true);
		}
		else if (_direction == Direction::Down) {
			animation->playAnimation("idle", true);
		}
		else if (_direction == Direction::Left) {
			animation->playAnimation("idleLeft", true);
		}
		else if (_direction == Direction::Right) {
			animation->playAnimation("idleRight", true);
		}
	}

	if (this->_velocity.x > this->_maxVelocity) {
		this->_velocity.x = this->_maxVelocity;
	}
	if (this->_velocity.y > this->_maxVelocity) {
		this->_velocity.y = this->_maxVelocity;
	}

	this->_entity->move(this->_velocity);
}
