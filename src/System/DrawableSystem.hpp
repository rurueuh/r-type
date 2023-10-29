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

                    if (!transform)
                        return;
                    drawHPBar(entity, transform, drawable, window);

                    drawDebugRect(drawable, transform, window);
                    drawSprite(drawable, transform, window);
                    });
    #endif
            }
#ifndef SERVER

            void drawHPBar(ECS::Entity* entity, TransformComponent* transform, DrawableComponent* drawable, sf::RenderWindow* window)
            {
                auto pv = entity->get<PvComponent>();
                if (pv) {
                    auto hpMax = pv->_maxHealth;
                    constexpr float maxHpBar = 100.f;
                    hpMax = std::max(hpMax, maxHpBar);
                    constexpr int offset = 20;
                    constexpr int height = 15;

                    sf::RectangleShape rectBack;
                    rectBack.setSize(sf::Vector2f((float)hpMax * 2, (float)height));
                    rectBack.setFillColor(sf::Color::Color(255, 255, 255, 150));
                    auto midX = transform->position.x + (drawable->sprite.getTextureRect().width * transform->scale.x) / 2;
                    rectBack.setPosition(midX - hpMax, transform->position.y - offset);

                    sf::RectangleShape rectFront;
                    rectFront.setSize(sf::Vector2f((float)pv->_health * 2, (float)height));
                    rectFront.setFillColor(sf::Color::Color(255, 0, 0, 255));
                    rectFront.setPosition(midX - hpMax, transform->position.y - offset);

                    window->draw(rectBack);
                    window->draw(rectFront);
                }
            }

            void drawSprite(DrawableComponent* drawable, TransformComponent* transform, sf::RenderWindow* window)
            {
                drawable->sprite.setPosition(transform->position);
                drawable->sprite.setScale(transform->scale);
                drawable->sprite.setRotation(transform->rotation);
                auto& sprite = drawable->sprite;
                window->draw(sprite);
            }

            void drawDebugRect(DrawableComponent* drawable, TransformComponent* transform, sf::RenderWindow* window)
            {
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(drawable->sprite.getTextureRect().width * transform->scale.x, drawable->sprite.getTextureRect().height * transform->scale.y));
                rect.setOutlineColor(sf::Color::Red);
                rect.setOutlineThickness(1);
                rect.setFillColor(sf::Color::Transparent);
                rect.setPosition(transform->position);
                window->draw(rect);
            }
#endif

        protected:
        private:
    };
}
