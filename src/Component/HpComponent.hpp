/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** HpComponent
*/

#pragma once

#include <bits/stdc++.h>
#include "Component.hpp"

class HpComponent : public Component {
    public:
        HpComponent(int hp) : _hp(hp) {};
        ~HpComponent() = default;

        std::string toString() const noexcept {
            std::string str = "\t\t\t HpComponent{";
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
