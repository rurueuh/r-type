/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** PatternSystem
*/

#pragma once
#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"

class PatternSystem : public ECS::BaseSystem {
    public:
        PatternSystem() = default;
        ~PatternSystem() = default;

        virtual void tick(ECS::World* world, const float& dt) override 
        {
            
        }

    protected:
    private:
};