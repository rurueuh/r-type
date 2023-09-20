#pragma once
#include "Level.h"
class Game final :
    public Level
{
public:
    Game();
    ~Game() = default;

    virtual void update(const float) override;
    virtual void draw(sf::RenderTarget &) override;

    bool operator==(const Game& other) const = default;
};

