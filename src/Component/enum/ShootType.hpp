/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** ShootType
*/

#pragma once
#include <iostream>

enum ShootType {
    LASER = 0,
    MISSILE,
    NONE


};

inline std::ostream &operator<<(std::ostream &os, const ShootType &type)
{
    switch (type) {
        case ShootType::LASER:
            os << "LASER";
            break;
        case ShootType::MISSILE:
            os << "MISSILE";
            break;
        case ShootType::NONE:
            os << "NONE";
            break;
    }
    return os;
}

inline std::istream &operator>>(std::istream &is, ShootType &type)
{
    std::string tmp;
    is >> tmp;
    if (tmp == "LASER")
        type = ShootType::LASER;
    else if (tmp == "MISSILE")
        type = ShootType::MISSILE;
    else if (tmp == "NONE")
        type = ShootType::NONE;
    return is;
}