#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"


class Enemy {
    private:
        sf::RectangleShape hitbox;
        // Animation *actual;

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

    public:
        Enemy(float x, float y);
        virtual ~Enemy();
        void update();
        void chooseDirection();
        void moving();
        void stopMoving(int next, int dir);
        void setCanGo(int dir, bool value);
        int getNextSpot(){return nextSpot;};
        void setDir();
        int getDirMoving(){return dirMoving;};
        bool getIsMoving(){return walking;};
        bool getDead(){return dead;};
        void setPosition();
        sf::FloatRect getGlobalBounds(){return hitbox.getGlobalBounds();};
        void setNextSpot(int next);
        void kill();
        sf::Vector2f getPosition(){return hitbox.getPosition();};
        void draw(sf::RenderWindow &window);

};