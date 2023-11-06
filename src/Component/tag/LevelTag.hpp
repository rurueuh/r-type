/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** LevelTag
*/

#pragma once

#include "ComponentBase.hpp"

/**
 * @brief Tag for level
 */
class LevelTag : public Component {
public:
    LevelTag() {};

    inline virtual std::string toString() const override {
        return "";
    }

    virtual void fromString(std::string str) override {
    }
    int fakeValue = 0;
};
