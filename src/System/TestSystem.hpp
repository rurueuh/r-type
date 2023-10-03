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

    virtual void tick(ECS::World *world, const float &dt) override {
        std::cout << "test" << std::endl;
    };
private:
};
