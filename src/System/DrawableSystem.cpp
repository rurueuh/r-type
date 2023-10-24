/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** DrawableSystem
*/

#include "DrawableSystem.hpp"
#include "GameEngine.hpp"

void DrawableSystem::tick(ECS::World *world, const float &dt)
{
    #ifndef SERVER
        auto window = GameEngine::GetInstance().getWindow();

        world->each<DrawableComponent>([&](ECS::Entity *entity, DrawableComponent *drawable) {
            auto transform = entity->get<TransformComponent>();
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(drawable->sprite.getTextureRect().width, drawable->sprite.getTextureRect().height));
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(1);
            rect.setFillColor(sf::Color::Transparent);
            rect.setPosition(transform->position);
            window->draw(rect);
            /**
             * 0 [VelocityComponent { 5.43704e-43 5.40901e-43 },TransformComponent { 966.859 258.329 4 4 010 10 1 1 0 },DrawableComponent { ../assets/player.png 1 3 32 14 },PvComponent { 207586 },InputComponent {  },PlayerComponent { 71383938681298111877845652246165 },:
             * 1 [VelocityComponent { -47.2552 5.40901e-43 },TransformComponent { 431.854 334.583 4 4 010 10 1 1 0 },DrawableComponent { ../assets/player.png 1 3 32 14 },PvComponent { 207586 },InputComponent { D },PlayerComponent { 40399875989090301191748290673539 },:
             * 2 [VelocityComponent { -5.49309e-43 5.49309e-43 },TransformComponent { 488.232 129.416 4 4 010 10 1 1 0 },DrawableComponent { ../assets/player.png 1 3 32 14 },PvComponent { 207586 },InputComponent {  },PlayerComponent { 58869538530454685502204123878165 },:
             * 3 [VelocityComponent { 84.5763 63.2605 },TransformComponent { 1204.35 293.254 4 4 010 10 1 1 0 },DrawableComponent { ../assets/player.png 1 3 32 14 },PvComponent { 207586 },InputComponent {  },PlayerComponent { 20736828175780958647761371718670 },:
            */

            if (!transform)
				return;
            // todo: move this to a system
            drawable->sprite.setPosition(transform->position);
            drawable->sprite.setScale(transform->scale);
            drawable->sprite.setRotation(transform->rotation);
            auto &sprite = drawable->sprite;
            window->draw(sprite);

        });
    #endif
}