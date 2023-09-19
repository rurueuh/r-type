#pragma once

#include "Level.hpp"
#include <vector>

class LevelManager
{
public:
	static LevelManager& getInstance()
	{
		static LevelManager instance;
		return instance;
	}

	template <typename T, typename... Args>
	void addLevel(Args&&... args)
	{
		#ifdef _DEBUG
		for (auto it = levels.begin(); it != levels.end(); ++it) {
			std::cout << typeid(*(*it)).name() << std::endl;
			std::cout << typeid(T).name() << std::endl;
			if (typeid(*(*it)) == typeid(T)) {
					std::cerr << "WARNING : Double level in LevelManager" << std::endl;
			}
		}
		#endif // _DEBUG
		std::shared_ptr<Level> level = std::make_shared<T>(std::forward<Args>(args)...);
		levels.push_back(level);
		if (!currentLevel)
			currentLevel = levels.back();
	}

	template <typename T>
	void setCurrentLevel()
	{
		for (auto& level : levels)
		{
			if (typeid(*level) == typeid(T))
			{
				currentLevel = level;
				return;
			}
		}
	}

	template <typename T>
	std::shared_ptr<T> getLevel()
	{
		for (auto& level : levels)
		{
			if (typeid(*level) == typeid(T))
			{
				return std::dynamic_pointer_cast<T>(level);
			}
		}
		return nullptr;
	}

	template <typename T>
	bool removeLevel(void) {
		for (auto it = levels.begin(); it != levels.end(); ++it) {
			if (typeid(*(*it)) == typeid(T)) {
				levels.erase(it);
				if (levels.size() > 0) {
					currentLevel = levels.back();
				}
				else {
					currentLevel = nullptr;
				}
				return true;
			}
		}
		return false;
	}

	void update(const float dt)
	{
		currentLevel->LevelUpdate(dt);
	}

	void draw(sf::RenderTarget& target)
	{
		currentLevel->LevelDraw(target);
	}

	LevelManager(LevelManager const&) = delete;
	bool operator==(const LevelManager& other) const = delete;

private:
	LevelManager() = default;
	LevelManager& operator=(LevelManager const&) = delete;

	std::vector<std::shared_ptr<Level>> levels;
	std::shared_ptr<Level> currentLevel;
};