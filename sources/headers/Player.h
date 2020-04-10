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

        bool isMoving = false;


        // Animations
        // Animation run = Animation("./resources/", size, velocity);

        Animation* currentAnim;
        
        Animation run_izq = Animation("./resources/pengo.png", 16, 0.15f);
        Animation run_der = Animation("./resources/pengo.png", 16, 0.15f);
        Animation run_up = Animation("./resources/pengo.png", 16, 0.15f);
        Animation run_down = Animation("./resources/pengo.png", 16, 0.15f);
        


    public:
        Player(int posx, int posy);
        virtual ~Player();
        void setMovement();
        void loadAnimations();
        void changeAnimation(Animation* newAnimation);
        void moving(float elapsedTime);

        void update(float elapsedTime);
        void draw(sf::RenderWindow& window);
};