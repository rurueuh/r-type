#pragma once

#include "Level.hpp"
#include "Component.hpp"
#include "SystemList.hpp"

class DevLevel : public Level {
public:
	DevLevel();
	~DevLevel();

	virtual void update(const float dt) override;
	
};