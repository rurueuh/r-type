#pragma once

#include "Level.hpp"

class DevLevel : public Level {
public:
	DevLevel();
	~DevLevel();

	virtual void update(const float dt) override;
	
};