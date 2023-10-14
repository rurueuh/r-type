/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** SpriteSystem
*/

#pragma once
#include "System.hpp"
#include "Component.hpp"

class SpriteSystem : public ECS::BaseSystem {
    public:
        SpriteSystem() = default;
        ~SpriteSystem() = default;

        virtual void tick(ECS::World* world, const float& dt) override;

    protected:
    private:
};
