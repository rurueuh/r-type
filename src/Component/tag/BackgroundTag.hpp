/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** BackgroundTag
*/

#pragma once

#include "ComponentBase.hpp"

/**
 * @brief Tag for background
*/
struct BackgroundTag : public Component {
    BackgroundTag() {};

    inline virtual std::string toString() const override {
        return "";
    }

    virtual void fromString(std::string str) override {
    }
    int fakeValue = 0;
};
