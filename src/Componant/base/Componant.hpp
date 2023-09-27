/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** Componant
*/

#pragma once

#include <bits/stdc++.h>

class Componant {
    public:
        Componant() = default;
        virtual ~Componant() = default;

        virtual std::string toString() const noexcept {
            std::string str = "\t\t\t BaseComponant{}";
            return str;
        };

    protected:
    private:
};
