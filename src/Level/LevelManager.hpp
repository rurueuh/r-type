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

	std::shared_ptr<Level> &getCurrentLevel(void) {
		return _currentLevel;
	}

	template <typename T>
	void setCurrentLevel() {
		for (auto &level : _levelLists) {
			if (typeid(*level) == typeid(T)) {
				_currentLevel = level;
				return;
			}
		}
	}

	template <typename T>
	void removeLevel() {
		for (auto it = _levelLists.begin(); it != _levelLists.end(); ++it) {
			if (typeid(**it) == typeid(T)) {
				if (_currentLevel == *it)
					_currentLevel = _levelLists.back();
				_levelLists.erase(it);
				return;
			}
		}
	}

private:
	LevelManager() = default;

	std::vector<std::shared_ptr<Level>> _levelLists = {};
	std::shared_ptr<Level> _currentLevel = {};
};