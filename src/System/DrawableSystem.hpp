/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** DrawableSystem
*/

#pragma once
#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"


namespace ECS::System {
    class DrawableSystem : public ECS::BaseSystem {
        public:
            DrawableSystem() = default;
            ~DrawableSystem() = default;

            virtual void tick(ECS::World* world, const float& dt) override
            {
    #ifndef SERVER
                auto window = GameEngine::GetInstance().getWindow();

                world->each<DrawableComponent>([&](ECS::Entity* entity, DrawableComponent* drawable) {
                    auto transform = entity->get<TransformComponent>();
                    sf::RectangleShape rect;
                    rect.setSize(sf::Vector2f(drawable->sprite.getTextureRect().width * transform->scale.x, drawable->sprite.getTextureRect().height * transform->scale.y));
                    rect.setOutlineColor(sf::Color::Red);
                    rect.setOutlineThickness(1);
                    rect.setFillColor(sf::Color::Transparent);
                    rect.setPosition(transform->position);

                    if (!transform)
                        return;
                    // todo: move this to a system
                    drawable->sprite.setPosition(transform->position);
                    drawable->sprite.setScale(transform->scale);
                    drawable->sprite.setRotation(transform->rotation);
                    auto& sprite = drawable->sprite;
                    window->draw(sprite);
                    //window->draw(rect);
                    });
    #endif
            }

        protected:
        private:
    };
}
