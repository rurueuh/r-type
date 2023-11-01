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

namespace ECS::System {
    class InputSystem : public ECS::BaseSystem {
        public:
            PatternSystem() = default;
            ~PatternSystem() = default;

            virtual void tick(ECS::World* world, const float& dt) override 
            {
                world->each<PatternComponent>(
                    [&](ECS::Entity* entity, PatternComponent* pattern, VelocityComponent* velocity) {
                        char direction = pattern->pattern[pattern->currentIndex];
                        switch(direction) {
                        case 'u':                           //Make the entity go Upward
                            velocity->velocity.y = -1.0f;
                            velocity->velocity.x = 0.0f;
                            break;
                        case 'd':                           //Make the entity go Downward
                            velocity->velocity.y = 1.0f;
                            velocity->velocity.x = 0.0f;
                            break;
                        case 'l':                           //Make the entity go Leftward
                            velocity->velocity.x = -1.0f;
                            velocity->velocity.y = 0.0f;
                            break;
                        case 'r':                           //Make the entity go Rightward
                            velocity->velocity.x = 1.0f;
                            velocity->velocity.y = 0.0f;
                            break;
                        case 'a':                           //Make the entity go diagonally Up and Left
                            velocity->velocity.x = -1.0f;
                            velocity->velocity.y = -1.0f;
                            break;
                        case 'e':                           //Make the entity go diagonally Up and Right
                            velocity->velocity.x = 1.0f;
                            velocity->velocity.y = -1.0f;
                            break;
                        case 'i':                           //Make the entity go diagonally Down and Left
                            velocity->velocity.x = -1.0f;
                            velocity->velocity.y = 1.0f;
                            break;
                        case 'y':                           //Make the entity go diagonally Down and Right
                            velocity->velocity.x = 1.0f;
                            velocity->velocity.y = 1.0f;
                            break;
                        case 'o':                           //Make the entity stay in place
                            velocity->velocity.x = 0.0f;
                            velocity->velocity.y = 0.0f;
                            break;
                    }
                        pattern->currentIndex = (pattern->currentIndex + 1) % pattern->pattern.length();
                    });
            }

        protected:
        private:
};
}