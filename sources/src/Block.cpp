#include "Block.h"

/*
Constructor of the block, it recieves a size, a position and a sprite
*/
Block::Block(sf::Texture &txt,sf::IntRect tamSprite, sf::Vector2f position)
{
    // hitbox = sf::RectangleShape(16);
    // hitbox.setPosition(position);
    sprite = sf::Sprite(txt, tamSprite);
    sprite.setPosition(position);
}

Block::~Block()
{
    
}

void Block::update()
{

}


/*
Just to use it as a gizmo to see if the block was drawn
*/
void Block::drawGizmo(sf::RenderWindow& window)
{
    window.draw(hitbox);
}

void Block::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
