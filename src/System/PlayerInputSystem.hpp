/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** PlayerInputSystem
*/

#pragma once

#include "System.hpp"
#include "Component.hpp"

class PlayerInputSystem : public ECS::BaseSystem {
    public:
        PlayerInputSystem();
        ~PlayerInputSystem();

		virtual void tick(ECS::World* world, const float& dt);

    protected:
    private:
};
