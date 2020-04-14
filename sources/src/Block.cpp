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

    x = position.x;
    y = position.y;
}

Block::~Block()
{
    
}

void Block::update(Player *player)
{

    if(hitbox.getGlobalBounds().intersects(player->topColision().getGlobalBounds())) 
    {
        player->setColision("UP", false);
        player->hasColided = true;
    }
    
    if(hitbox.getGlobalBounds().intersects(player->bottomColision().getGlobalBounds())) 
    {
        player->setColision("DOWN", false);
        player->hasColided = true;
    } 
    
    if(hitbox.getGlobalBounds().intersects(player->leftColision().getGlobalBounds())) 
    {
        player->setColision("LEFT", false);
        player->hasColided = true;
    }
    
    if(hitbox.getGlobalBounds().intersects(player->rightColision().getGlobalBounds())) 
    {
        player->setColision("RIGHT", false);
        player->hasColided = true;
    }

}

void Block::update2()
{
    //std::cout << "llamandose"<< std::endl;
    if(isMoving) 
    {
        if(dir.compare("UP") == 0) 
        {
            y-=moveSpeed;
            if( y <= nextSpot) {
                y = nextSpot;
                isMoving = false;
            }
        }
        else if(dir.compare("DOWN") == 0)
        {
            
        }

    }
    hitbox.setPosition(x, y);
    sprite.setPosition(x, y);
}

void Block::setNextSpot(int next)
{
    isMoving = true;
    nextSpot = next;
    std::cout << "NEXSPOT: " << nextSpot << std::endl;
    std::cout << "ACTUAL SPOT: " << y << std::endl;
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
