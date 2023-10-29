#pragma once

#include "Level.hpp"
#include "Component.hpp"
#include "SystemList.hpp"

class DeadLevel : public Level {
public:
	DeadLevel();
	~DeadLevel();

	virtual void update(const float dt) override;
private:
};