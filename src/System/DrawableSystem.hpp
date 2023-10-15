/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** DrawableSystem
*/

#pragma once
#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"

class DrawableSystem : public ECS::BaseSystem {
    public:
        DrawableSystem() = default;
        ~DrawableSystem() = default;

        virtual void tick(ECS::World* world, const float& dt) override;

    protected:
    private:
};
