#pragma once

#include "Level.hpp"
#include <vector>

class LevelManager
{
public:
	static LevelManager& getInstance() {
		static LevelManager instance;
		return instance;
	}

	template <typename T, typename... Args>
	void addLevel(Args&&... args) {
		std::shared_ptr<Level> level = std::make_shared<T>(std::forward<Args>(args)...);
		_levelLists.push_back(level);
		if (!_currentLevel)
			_currentLevel = _levelLists.back();
	}

	void update(const float dt = 0) {
		_currentLevel->update(dt);
		auto* world = _currentLevel->getWorld();
		world->tick(dt);
	}

private:
	LevelManager() = default;

	std::vector<std::shared_ptr<Level>> _levelLists = {};
	std::shared_ptr<Level> _currentLevel = {};
};