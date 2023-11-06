#pragma once

#include "Level.hpp"
#include "Component.hpp"
#include "SystemList.hpp"

typedef struct {
	std::string path;
	sf::IntRect area;
	float speed;
} infoBackground_t;

typedef struct infoEnemySpawn_s{
	float time = 0.f;
	sf::Vector2f position = sf::Vector2f(0.f, 0.f);
	short hp = 1;
	bool operator== (const infoEnemySpawn_s& other) {
		return (time == other.time && position == other.position && hp == other.hp);
	}
} infoEnemySpawn_t;

class DevLevel : public Level {
public:
	DevLevel();
	void CreatePlayers();
	void CreateBackground(sf::RenderWindow* window, sf::Vector2u& size);
	~DevLevel();

	virtual void update(const float dt) override;
	void BackgroundParallax();
private:
	std::vector<ECS::Entity*> _backgrounds = _world->CreateEntity(10);
	
	std::vector<infoBackground_t> _infoBackgrounds = {
		{"../assets/back1.png", sf::IntRect(0, 0, 272, 160), -80},
		{"../assets/back2.png", sf::IntRect(0, 0, 272, 160), -50},
		{"../assets/back3.png", sf::IntRect(0, 0, 272, 160), -30},
		{"../assets/back4.png", sf::IntRect(0, 0, 272, 160), -120},
		{"../assets/back5.png", sf::IntRect(0, 0, 272, 160), -150},
	};

	std::vector<infoEnemySpawn_t> _infoEnemy = {
		{ 0.f, sf::Vector2f(1600.f, 0.f), 60 },
		{ 0.f, sf::Vector2f(1600.f, 900.f), 60 },
		{ 2.f, sf::Vector2f(1000.f, 0.f), 60 },
		{ 2.f, sf::Vector2f(1000.f, 900.f), 60 },
		{ 4.f, sf::Vector2f(1000.f, 0.f), 60 },
		{ 4.f, sf::Vector2f(1000.f, 900.f), 60 },
		{ 6.f, sf::Vector2f(1000.f, 0.f), 60 },
		{ 6.f, sf::Vector2f(1000.f, 900.f), 60 },
		{ 8.f, sf::Vector2f(1000.f, 0.f), 60 },
		{ 8.f, sf::Vector2f(1000.f, 900.f), 60 },
	};
	sf::Clock _clockEnemy;

	std::vector<sf::IntRect> _infoPlayers = {
		sf::IntRect(1, 3, 32, 14),
		sf::IntRect(1, 20, 32, 14),
		sf::IntRect(1, 37, 32, 14),
		sf::IntRect(1, 54, 32, 14),
		sf::IntRect(1, 71, 32, 14),
	};
};