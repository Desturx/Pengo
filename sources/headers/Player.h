#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"

class Player {
    private:
        sf::RectangleShape hitbox;
        // Animations
        Animation* currentAnim;
        // Animation run = Animation("./resources/", size, velocity);

    public:
        Player(sf::Vector2f position);
        virtual ~Player();
        void update(float elapsedTime);
        void draw(sf::RenderWindow& window);
};