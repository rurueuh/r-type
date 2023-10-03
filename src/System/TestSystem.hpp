/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TestSystem
*/

#pragma once

#include "System.hpp"
#include <iostream>

class TestSystem : public ECS::BaseSystem {
public:
    TestSystem() = default;
    ~TestSystem() = default;

    virtual void tick(ECS::World* world, const float& dt) override;
private:
};

class TestESystem : public ECS::BaseSystem {
public:
    TestESystem() = default;
    ~TestESystem() = default;

    virtual void tick(ECS::World* world, const float& dt) override {
        std::cout << "teste" << std::endl;
    };
private:
};

