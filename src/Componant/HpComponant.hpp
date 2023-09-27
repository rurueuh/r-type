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

        int getHp() const { return _hp; };
        void setHp(int hp) { _hp = hp; };

    protected:
    private:
        int _hp = 100;
};