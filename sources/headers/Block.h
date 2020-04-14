#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class Block {
    public:
        Block(sf::Texture &texture,sf::IntRect tamSprite, sf::Vector2f position);
        virtual ~Block();
        void update(Player *player);
        void update2(Player *player);
        void draw(sf::RenderWindow &window);
        void drawGizmo(sf::RenderWindow &window);
        sf::FloatRect getGlobalBounds();
        sf::Vector2f getPosition();
        void setNextSpot(int nextSpot, std::string direction);
        bool getMoving(){return isMoving;}

    private:
        sf::RectangleShape hitbox;
        sf::Sprite sprite;
        bool isMoving  = false;
        int x, y, nextSpot;
        float moveSpeed = 4.f;
        std::string dir;
        std::string dirIsColliding;

};