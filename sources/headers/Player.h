#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"

class Player {
    private:
        sf::RectangleShape hitbox;

        int tilesize = 16;

        float x;
        float y;

        float movespeed;
        enum MOVE {UP,DOWN,LEFT,RIGHT};
        bool move[4];
        bool walking;
        int nextspot;

        int nextX;
        int nextY;


        // Animations
        Animation* currentAnim;
        // Animation run = Animation("./resources/", size, velocity);
       
       

    public:
        Player(sf::Vector2f position);
        virtual ~Player();
        void setMovement();
        void moving(float elapsedTime);
        
        void update(float elapsedTime);
        void draw(sf::RenderWindow& window);
};