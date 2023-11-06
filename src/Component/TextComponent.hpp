#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"
#include <iostream>

/**
 * @brief Component for text
 * @details The text is a string
 * @todo Add font
*/
class TextComponent : public Component {
public:
    /**
     * @brief Construct a new Text Component object
     * @param text The text
    */
    TextComponent(std::string text) : _text(text) {};
    TextComponent() : _text("") {};

    /**
     * @brief Put the text on string
     * @return The string of the text
    */
    inline virtual std::string toString() const override {
        return _text;
    }

    /// @brief Construct the text from string
    /// @param str The string of the text
    virtual void fromString(std::string str) override {
        _text = str;
    }

    std::string _text = "";
    #ifndef SERVER
        sf::Text sfText;
    #endif
};
