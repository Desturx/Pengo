#include "Block.h"

/*
Constructor of the block, it recieves a size, a position and a sprite
*/
Block::Block(sf::Texture &txt,sf::IntRect tamSprite, sf::Vector2f position)
{
    hitbox = sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    hitbox.setPosition(position);
    sprite = sf::Sprite(txt, tamSprite);
    sprite.setPosition(position);
}

Block::~Block()
{
    
}

void Block::update(Player *player)
{
    // hacer un check para que solo haga las comprobaciones si la distancia del jugador al bloque es 16 pixels
    std::cout << "Entró" << std::endl;
    if(hitbox.getGlobalBounds().intersects(player->topColision().getGlobalBounds())) {
        // std::cout << "SE COLISIONAROOOON" << std::endl;
        //player->test();

    }
    

}

sf::FloatRect Block::getGlobalBounds()
{
    return hitbox.getGlobalBounds();
}

sf::Vector2f Block::getPosition()
{
    return hitbox.getPosition();
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
