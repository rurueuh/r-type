#pragma once

#include "Level.hpp"
#include "Component.hpp"
#include "SystemList.hpp"

typedef struct infoBackground {
	std::string path;
	sf::IntRect area;
	float speed;
} infoBackground;

class FirstLevel : public Level {
	public:
		FirstLevel();
		void CreatePlayers();
		void CreateBackground(sf::RenderWindow* window, sf::Vector2u& size);
		void CreateWall(sf::RenderWindow* window, sf::Vector2u& size);
		void CreateEnemies(size_t id);
		~FirstLevel();

		virtual void update(const float dt) override;
		void BackgroundParallax();
		void ScrollWalls(const float dt);
	private:
		std::vector<ECS::Entity*> _backgrounds = _world->CreateEntity(10);
		
		std::vector<infoBackground> _infoBackgrounds = {
			{"./assets/back1.png", sf::IntRect(0, 0, 272, 160), -80},
			{"./assets/back2.png", sf::IntRect(0, 0, 272, 160), -50},
			{"./assets/back3.png", sf::IntRect(0, 0, 272, 160), -30},
			{"./assets/back4.png", sf::IntRect(0, 0, 272, 160), -120},
			{"./assets/back5.png", sf::IntRect(0, 0, 272, 160), -150},
		};

		std::vector<sf::IntRect> _infoPlayers = {
			sf::IntRect(1, 3, 32, 14),
			sf::IntRect(1, 20, 32, 14),
			sf::IntRect(1, 37, 32, 14),
			sf::IntRect(1, 54, 32, 14),
			sf::IntRect(1, 71, 32, 14),
		};
};