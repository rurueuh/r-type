/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** Component
*/

#pragma once

#include <bits/stdc++.h>
#include "macro.hpp"

class Component {
    public:
        Component() = default;
        virtual ~Component() = default;

        virtual std::string toString() const noexcept {
            std::string str = "\t\t\t BaseComponent{}";
            return str;
        };

    protected:
    private:
};
