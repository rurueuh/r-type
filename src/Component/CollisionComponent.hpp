#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"


namespace ECS::Collision {
    enum CollisionType {
	    PLAYER,
	    ENEMY,
	    BULLET_ENEMY,
        BULLET_PLAYER,
	    WALL,
	    NONE
    };
}

struct CollisionComponent : public Component {
    CollisionComponent(sf::FloatRect rect, ECS::Collision::CollisionType type) : _rect(rect), _type(type) {};
    CollisionComponent() : _rect(0.f, 0.f, 0.f, 0.f), _type(ECS::Collision::NONE) {};

    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(_rect.left) + " ";
        str += std::to_string(_rect.top) + " ";
        str += std::to_string(_rect.width) + " ";
        str += std::to_string(_rect.height) + " ";
        str += std::to_string(_type);
        return str;
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> _rect.left;
        ss >> _rect.top;
        ss >> _rect.width;
        ss >> _rect.height;
        int type;
        ss >> type;
        _type = static_cast<ECS::Collision::CollisionType>(type);

    }

    sf::FloatRect _rect = sf::FloatRect(0.f, 0.f, 0.f, 0.f);
    ECS::Collision::CollisionType _type = ECS::Collision::NONE;
};