#include "Game.h"
#include "Player.h"

Game::Game() : Level()
{
	this->addEntity<Player>();
}

void Game::update(const float dt)
{
}

void Game::draw(sf::RenderTarget& target)
{

}