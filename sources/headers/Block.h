#pragma once
#include <SFML/Graphics.hpp>

class Block {
    public:
        Block(sf::Texture &texture,sf::IntRect tamSprite, sf::Vector2f position);
        virtual ~Block();
        void update();
        void draw(sf::RenderWindow &window);
        void drawGizmo(sf::RenderWindow &window);

    private:
        sf::RectangleShape hitbox;
        sf::Sprite sprite;
};