#pragma once

#include "Level.hpp"
#include "Component.hpp"
#include "SystemList.hpp"

class LobbyLevel : public Level {
public:
	LobbyLevel();
	~LobbyLevel();

	virtual void update(const float dt) override;
private:
};