#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"
#include <iostream>

struct TextComponent : public Component {
    TextComponent(std::string text) : _text(text) {};
    TextComponent() : _text("") {};

    inline virtual std::string toString() const override {
        return _text;
    }

    virtual void fromString(std::string str) override {
        _text = str;
    }

    std::string _text = "";
    #ifndef SERVER
    sf::Text sfText;
    #endif
};
