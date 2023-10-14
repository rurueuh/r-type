/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** DamageComponent
*/

#pragma once

struct DamageComponent {
    DamageComponent(int damage) : damage(damage) {};
    DamageComponent() : damage(0) {};
    int damage;
};