#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation {
    private:
        sf::Sprite sprite;
        sf::Texture texture;

        sf::IntRect firstF;
        sf::IntRect lastF;
        sf::IntRect actualF;

        sf::Clock clock;
        int sprSize;
        float animVel;

    public:
        Animation(char* textureName, int sprSize, float animationVelocity);
        virtual ~Animation();

        void setFrames(sf::IntRect firstFrame, sf::IntRect lastFrame);
        void setPosition(sf::Vector2f pos);

        void update();
        void draw(sf::RenderWindow& window);
};