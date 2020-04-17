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

        std::string lastPosition = "DOWN";

        bool walking;
        int nextspot;

        bool playingAnimation = false;

        // colision boxes
        sf::RectangleShape colisions[4];
        bool canMove[4];



        // Animations
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
        void pushingBlocks(std::string direction);
        // void checkColisions(std::vector<Block*> blocks);
        sf::RectangleShape topColision();
        sf::RectangleShape bottomColision();
        sf::RectangleShape leftColision();
        sf::RectangleShape rightColision();

        void setColision(std::string dir, bool value);

        sf::Vector2f getPosition();
        void moveColisions();

        std::string getDirection(){return lastPosition;}
        bool isMoving(){return walking;};

        void update(float elapsedTime);
        void draw(sf::RenderWindow& window);
        bool hasColided = false;
        
};