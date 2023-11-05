#pragma once

#include "Level.hpp"
#include "Component.hpp"
#include "SystemList.hpp"

class WinLevel : public Level {
public:
	WinLevel();
	~WinLevel();

	virtual void update(const float dt) override;
private:
};