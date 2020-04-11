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

        bool loop = true;
        bool finished = false;
        bool isPlaying = true;
        int loopNumbers = 0;
        int times = 0;

    public:
        Animation(std::string textureName, int sprSize, float animationVelocity);
        virtual ~Animation();

        void setFrames(sf::IntRect firstFrame, sf::IntRect lastFrame);
        void setPosition(sf::Vector2f pos);

        void noLoop();
        void update();
        void play();
        void stop();

        bool isFinished();

        void loopXtimes(int timesToLoop);
        void reset();
        
        void draw(sf::RenderWindow& window);
};