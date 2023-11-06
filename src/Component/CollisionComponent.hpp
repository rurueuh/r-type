#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"


namespace ECS::Collision {
    /**
     * @brief Enum for collision type
     * @details Used to know what type of collision we have
    */
    enum CollisionType {
	    PLAYER,
	    ENEMY,
	    BULLET_ENEMY,
        BULLET_PLAYER,
	    WALL,
	    NONE
    };
}

/**
 * @brief Component for collision
 * @details Used to know if an entity is colliding with another
*/
class CollisionComponent : public Component {
public:
    /**
     * @brief Construct a new Collision Component object
     * @param rect The rect of the collision
     * @param type The type of the collision
     * @details The rect is the rect of the entity
     * The type is the type of the entity
    */
    CollisionComponent(sf::FloatRect rect, ECS::Collision::CollisionType type) : _rect(rect), _type(type) {};
    CollisionComponent() : _rect(0.f, 0.f, 0.f, 0.f), _type(ECS::Collision::NONE) {};


    /**
     * @brief Put the collision on string
     * @return The string of the collision
    */
    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(_rect.left) + " ";
        str += std::to_string(_rect.top) + " ";
        str += std::to_string(_rect.width) + " ";
        str += std::to_string(_rect.height) + " ";
        str += std::to_string(_type);
        return str;
    }

    /// @brief Construct the collision from string
    /// @param str The string of the collision
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

    /**
     * @brief Get the rect of the collision
    */
    sf::FloatRect _rect = sf::FloatRect(0.f, 0.f, 0.f, 0.f);
    /**
     * @brief Get the type of the collision
    */
    ECS::Collision::CollisionType _type = ECS::Collision::NONE;
};