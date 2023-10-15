/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** transformSystem
*/

#pragma once
#include "Component.hpp"
#include "System.hpp"

class TransformSystem : public ECS::BaseSystem {
    public:
        TransformSystem() = default;
        ~TransformSystem() = default;

        virtual void tick(ECS::World* world, const float& dt) override;

    protected:
    private:
};