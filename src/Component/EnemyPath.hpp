#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"

enum EnemyPathType {
    FOLLOW_PLAYER,

};

struct EnemyPath : public Component {
    EnemyPath(EnemyPathType type) : pathType(type) {};
    EnemyPath() : pathType(FOLLOW_PLAYER) {};

    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(pathType) + " ";
        str += std::to_string(_isDownMove);
        return str;
    }

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
