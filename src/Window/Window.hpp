#pragma once

#include "SFML.hpp"
#include <memory>

class Window
{
public:
	static Window& getInstance(void) {
		static Window instance;
		return instance;
	}
private:
	Window(const int x = 1920, const int y = 1080, const int fpsMax = 0, const std::string title = "SFML");
	~Window() = default;
	std::shared_ptr<sf::RenderWindow> _window;
};
