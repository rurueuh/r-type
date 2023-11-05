#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"

struct AnimationComponent : public Component {
    AnimationComponent(std::vector<sf::IntRect> anims, float time) : animFrame(anims), timeSwitch(time) {};
    AnimationComponent() = default;

    inline virtual std::string toString() const override {
        std::string str = "";
        int size = animFrame.size();
        str += std::to_string(size) + " ";
        for (int i = 0; i < size; i++) {
            str += std::to_string(animFrame[i].left) + " ";
            str += std::to_string(animFrame[i].top) + " ";
            str += std::to_string(animFrame[i].width) + " ";
            str += std::to_string(animFrame[i].height) + " ";
        }
        str += std::to_string(timeSwitch) + " ";
        str += std::to_string(clockTime) + " ";
        str += std::to_string(actualFrame) + " ";
        return str;
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        int size = 0;
        ss >> size;
        for (int i = 0; i < size; i++) {
            sf::IntRect rect;
            ss >> rect.left >> rect.top >> rect.width >> rect.height;
            animFrame.push_back(rect);
        }
        ss >> timeSwitch;
        ss >> clockTime;
        ss >> actualFrame;
    }

    std::vector<sf::IntRect> animFrame = {};
    float timeSwitch = 0.f;
    float clockTime = 0.f;
    int actualFrame = 0;
};
