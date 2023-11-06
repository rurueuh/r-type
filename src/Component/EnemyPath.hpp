#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"

/**
 * @brief enum for enemy path type
*/
enum EnemyPathType {
    FOLLOW_PLAYER,
    FOLLOW_PLAYER_BOSS,
    FOLLOW_PATH,
    FOLLOW_PATH_BOSS,
};

/**
 * @brief Component for enemy path
*/
class EnemyPath : public Component {
public:
    /**
     * @brief Construct a new Enemy Path object
     * @param type The type of the path
    */
    EnemyPath(EnemyPathType type) : pathType(type) {
        _isDownMove = (rand() % 2) == 0;
    };
    EnemyPath() : pathType(FOLLOW_PLAYER) {};

    /**
     * @brief Put the enemy path on string
     * @return The string of the enemy path
    */
    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(pathType) + " ";
        str += std::to_string(_isDownMove);
        return str;
    }

    /// @brief Construct the enemy path from string
    /// @param str The string of the enemy path
    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        int type;
        ss >> type;
        pathType = static_cast<EnemyPathType>(type);
        ss >> _isDownMove;
    }

    EnemyPathType pathType = FOLLOW_PLAYER;
    bool _isDownMove = false;
};
