#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"


namespace ECS {
    namespace System {
        class TextSystem : public ECS::BaseSystem {
        public:
            TextSystem() = default;
            ~TextSystem() = default;

            virtual void tick(ECS::World* world, const float& dt) override {
                world->each<TextComponent>([&](ECS::Entity* ent, TextComponent* text) {
                    #ifndef SERVER
                    text->sfText.setString(text->_text);
                    text->sfText.setFont(GameEngine::GetInstance().getFont());
                    text->sfText.setCharacterSize(30);
                    text->sfText.setFillColor(sf::Color::White);

                    auto transform = ent->get<TransformComponent>();
                    if (transform) {
                        text->sfText.setPosition(transform->position);
                        text->sfText.setRotation(transform->rotation);
                        text->sfText.setScale(transform->scale);
                    }

                    auto window = GameEngine::GetInstance().getWindow();
                    window->draw(text->sfText);
                    #endif
                });
            }
        private:
        };
    }
}