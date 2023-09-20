#pragma once
#include "Component.h"
class ControllerMouvement final :
    public Component
{
public:
    ControllerMouvement(Entity* entity) : Component(entity, true, false) {};
	~ControllerMouvement() {};

	void update(float dt) override;
	void draw(sf::RenderTarget& window) override {};

	bool isMoving() const { return _isMoving; }
	void setMoving(bool moving) { _isMoving = moving; }

	Direction getDirection() const { return _direction; }
	void setDirection(Direction direction) { _direction = direction; }

	void addVelocity(sf::Vector2f velocity) { _velocity += velocity; }
	void setVelocity(sf::Vector2f velocity) { _velocity = velocity; }
	sf::Vector2f getVelocity() const { return _velocity; }

private:
	sf::Clock _clock;
	const float _timeUpdate = 0.01f;
	sf::Vector2f _velocity = {};
	const float _maxVelocity = 20.0f;
	const float _acceleration = 5.f;
	const float _deceleration = 5.f;
	Direction _direction = Direction::Down;

	bool _isMoving = false;
};

