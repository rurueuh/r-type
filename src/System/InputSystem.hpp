/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** InputSystem
*/

#pragma once
#include "Component.hpp"
#include "System.hpp"
#include "World.hpp"

class InputSystem : public ECS::BaseSystem {
public:
    InputSystem() = default;
    ~InputSystem() = default;

    virtual void tick(ECS::World* world, const float& dt) override;

protected:
private:
};