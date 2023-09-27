/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** HpComponant
*/

#pragma once

#include <bits/stdc++.h>
#include "Componant.hpp"

class HpComponant : public Componant {
    public:
        HpComponant() = default;
        ~HpComponant() = default;

        std::string toString() const noexcept {
            std::string str = "\t\t\t HpComponant{";
            str += "\n\t\t\t\tHp: " + std::to_string(_hp);
            str += "\n\t\t\t}";
            return str;
        };

        int getHp() const { return _hp; };
        void setHp(int hp) { _hp = hp; };

    protected:
    private:
        int _hp = 100;
};
