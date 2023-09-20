#pragma once

void Event(std::shared_ptr<sf::RenderWindow>& window);

void draw(std::shared_ptr<sf::RenderWindow>& window, LevelManager& levelManager);

void Update(LevelManager& levelManager);
