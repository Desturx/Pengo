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

        std::string lastPosition = "RIGHT";

        bool walking;
        int nextspot;

        bool playingAnimation = false;


        // Animations
        // Animation run = Animation("./resources/", size, velocity);

        Animation* currentAnim;
        std::string textureSrc = "./resources/pengo.png";
        
        Animation run_left = Animation(textureSrc, 16, 0.15f);
        Animation run_right = Animation(textureSrc, 16, 0.15f);
        Animation run_up = Animation(textureSrc, 16, 0.15f);
        Animation run_down = Animation(textureSrc, 16, 0.15f);

        Animation push_left = Animation(textureSrc, 16, 0.15f);
        Animation push_right = Animation(textureSrc, 16, 0.15f);
        Animation push_up = Animation(textureSrc, 16, 0.15f);
        Animation push_down = Animation(textureSrc, 16, 0.15f);


        
        


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