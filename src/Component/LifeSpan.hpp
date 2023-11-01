#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"

struct LifeSpan : public Component {
    LifeSpan(float time) : _time(time) {};
    LifeSpan() : _time(0.f) {};

    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(_time);
        return str;
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> _time;
    }

    float _time = 0.f;
};
