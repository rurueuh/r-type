#pragma once

struct PvComponent {
    PvComponent(int health) : health(health) {};
    PvComponent() : health(0) {};
    int health = 0;
};
