#include "Menu.h"
#include "LevelManager.h"
#include "Game.h"

Menu::Menu()
{
	_background = std::make_shared<Image>("assets/background.jpg", sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
	_playButton = std::make_shared<TextButton>("PLAY", 24, "assets/rpg.ttf", sf::Vector2f(350, 50), sf::Vector2f(1920/2 - 350 / 2, 300), true);
}

Menu::~Menu()
{
	TextureManager::clear();
}

void Menu::update(const float dt)
{
	_playButton->update();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _playButton->isHover()) {
		LevelManager& levelManager = LevelManager::getInstance();
		levelManager.addLevel<Game>();
		levelManager.removeLevel<Menu>();
	}
}

void Menu::draw(sf::RenderTarget& target)
{
	_background->draw(target);
	_playButton->draw(target);
}
