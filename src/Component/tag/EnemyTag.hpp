/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** EnemyTag
*/

#pragma once

#include "ComponentBase.hpp"

struct EnemyTag : public Component {
    EnemyTag() {};

    virtual std::string toString() override {
        return "EnemyTag";
    }

    virtual void fromString(std::string str) override {
    }
    int fakeValue = 0;
};
