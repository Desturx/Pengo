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
        dirIsColliding = "UP";
    }
    
    if(hitbox.getGlobalBounds().intersects(player->bottomColision().getGlobalBounds())) 
    {
        player->setColision("DOWN", false);
        player->hasColided = true;
        dirIsColliding = "DOWN";
    } 
    
    if(hitbox.getGlobalBounds().intersects(player->leftColision().getGlobalBounds())) 
    {
        player->setColision("LEFT", false);
        player->hasColided = true;
        dirIsColliding = "LEFT";
    }
    
    if(hitbox.getGlobalBounds().intersects(player->rightColision().getGlobalBounds())) 
    {
        player->setColision("RIGHT", false);
        player->hasColided = true;
        dirIsColliding = "RIGHT";
    }


}

void Block::update2(Player *player)
{
    //std::cout << "llamandose"<< std::endl;
    if(isMoving) 
    {
        player->pushingBlocks(dir);

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
            y+=moveSpeed;
            if( y >= nextSpot) {
                y = nextSpot;
                isMoving = false;
            }
        }
        else if(dir.compare("LEFT") == 0)
        {
            x-=moveSpeed;
            if( x <= nextSpot) {
                x = nextSpot;
                isMoving = false;
            }
        }
        else if(dir.compare("RIGHT") == 0)
        {
            x+=moveSpeed;
            if( x >= nextSpot) {
                x = nextSpot;
                isMoving = false;
            }
        }


        hitbox.setPosition(x, y);
        sprite.setPosition(x, y);

        
        player->setColision(player->getDirection(), true);
        //player->hasColided = false;
    }
}

void Block::setNextSpot(int next, std::string direction)
{
    if(direction.compare(dirIsColliding) == 0)
    {
        isMoving = true;
        nextSpot = next;
        dir = direction;
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
