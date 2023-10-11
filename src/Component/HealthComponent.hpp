/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** HealthComponent
*/

#pragma once

struct HealthComponent {
    HealthComponent(int health) : health(health) {};
    HealthComponent() : health(0) {};
    int health;
};