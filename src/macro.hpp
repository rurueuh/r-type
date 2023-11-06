/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** macro
*/

#pragma once

#define PRINT_ERROR(x) std::cerr << "ERROR : " << x << std::endl;
#include <iostream>

#define DCC sf::Clock debugClock; debugClock.restart();
#define DCP std::cout << std::fixed << "DEBUG : " << debugClock.getElapsedTime().asSeconds() << "s" << std::endl;

#define DEBUG_CLOCK static sf::Clock debugClock; if (debugClock.getElapsedTime().asSeconds() > 0.1) { std::cout << std::fixed << "DEBUG : " << debugClock.getElapsedTime().asSeconds() << "s" << std::endl; debugClock.restart(); }