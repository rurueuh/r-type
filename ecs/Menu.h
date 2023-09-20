#pragma once
#include "Level.h"

class Menu :
    public Level
{
public:
	Menu();
	virtual ~Menu();

	void update(const float dt) override;
	void draw(sf::RenderTarget& target) override;

	private:
		std::shared_ptr<Image> _background;
		std::shared_ptr<TextButton> _playButton;
};

