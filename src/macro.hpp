/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** macro
*/

#pragma once

#define PRINT_ERROR(x) std::cerr << "ERROR : " << x << std::endl;
#include <iostream>

#define DEBUG_CLOCK_CREATE sf::Clock debugClock; debugClock.restart();
#define DEBUG_CLOCK_PRINT std::cout << "DEBUG : " << debugClock.getElapsedTime().asSeconds() << "s" << std::endl;
