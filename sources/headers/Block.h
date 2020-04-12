#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class Block {
    public:
        Block(sf::Texture &texture,sf::IntRect tamSprite, sf::Vector2f position);
        virtual ~Block();
        void update(Player *player);
        void draw(sf::RenderWindow &window);
        void drawGizmo(sf::RenderWindow &window);
        sf::FloatRect getGlobalBounds();
        sf::Vector2f getPosition();

    private:
        sf::RectangleShape hitbox;
        sf::Sprite sprite;
};