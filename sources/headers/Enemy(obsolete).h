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
        float movespeed = 1.2f;
        int x, y;
        int dirMov = 0;
        int nextSpot = 0;

    public:
        Enemy(float x, float y);
        virtual ~Enemy();
        void moving();
        void setPosition();
        void setDir();
        void stopMoving(int dir);
        void setCanGo(int dir, bool value);
        int getDir(){return dirMov;};
        void setNextSpot(int spot);
        bool getWalking(){return walking;};
        sf::Vector2f getPosition(){return hitbox.getPosition();};
        void draw(sf::RenderWindow &window);

};