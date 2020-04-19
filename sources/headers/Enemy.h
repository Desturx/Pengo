#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"


class Enemy {
    private:
        sf::RectangleShape hitbox;
        Animation *actual;

        enum MOVE {UP,DOWN,LEFT,RIGHT};
        bool move[4];
        bool canGo[4];
        bool walking = false;
        bool ready = false;
        float movespeed = 1.8f;
        sf::Clock clock;
        int x, y;
        int lastX, lastY;
        int nextSpot;
        int dirMoving = 0;

    public:
        Enemy(float x, float y);
        virtual ~Enemy();
        void update();
        void chooseDirection();
        void moving();
        void stopMoving(int next, int dir);
        int getNextSpot(){return nextSpot;};
        int getDirMoving(){return dirMoving;};
        bool getIsMoving(){return walking;};
        sf::Vector2f getPosition(){return hitbox.getPosition();};
        void draw(sf::RenderWindow &window);

};