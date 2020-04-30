#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"


class Enemy {
    private:
        sf::RectangleShape hitbox;

        enum MOVE {UP,DOWN,LEFT,RIGHT};
        bool move[4];
        bool canGo[4];
        bool collides[4];
        bool walking = false;
        bool ready = false;
        bool dead = false;
        float movespeed = 1.f;
        sf::Clock clock;
        int x, y;
        int lastX, lastY;
        int nextSpot;
        int dirMoving = 0;

        bool doNothing = false;

        // Animations
        Animation *currentAnim;
        std::string textureSrc = "./resources/snowbee.png";

        Animation run_left = Animation(textureSrc, 16, 0.15f);
        Animation run_right = Animation(textureSrc, 16, 0.15f);
        Animation run_up = Animation(textureSrc, 16, 0.15f);
        Animation run_down = Animation(textureSrc, 16, 0.15f);
        
        Animation eggSpawn = Animation(textureSrc, 16, 0.15f);


    public:
        Enemy(float x, float y);
        virtual ~Enemy();
        void loadAnimations();
        void update();
        void chooseDirection();
        void moving();
        void changeAnimation(Animation* newAnimation);
        void stopMoving(int next, int dir);
        void setCanGo(int dir, bool value);
        void setDir();
        void setPosition();
        void setNextSpot(int next);
        void kill();
        int getNextSpot(){return nextSpot;};
        int getDirMoving(){return dirMoving;};
        bool getIsMoving(){return walking;};
        bool getDead(){return dead;};
        sf::FloatRect getGlobalBounds(){return hitbox.getGlobalBounds();};
        sf::Vector2f getPosition(){return hitbox.getPosition();};
        bool getDoNothing(){return doNothing;};
        void draw(sf::RenderWindow &window);

};