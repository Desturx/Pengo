#include "Block.h"

/*
Constructor of the block, it recieves a size, a position and a sprite
blockType = "SPECIAL" or "NORMAL"
*/
Block::Block(sf::Texture &txt,sf::IntRect tamSprite, sf::Vector2f position, std::string blockType)
{
    type = blockType;

    hitbox = sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    hitbox.setPosition(position);
    sprite = sf::Sprite(txt, tamSprite);
    sprite.setPosition(position);

    using namespace sf;
    breaking.setFrames(IntRect(16*0, 0, 16, 16), IntRect(16*8, 0, 16, 16));
    breaking.loopXtimes(1);

    breaking.setPosition(position);

    x = position.x;
    y = position.y;
}

Block::~Block()
{
    
}

/*
Is called only when the block is stopped
*/
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
    //player->pushingBlocks(dir);

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
        breaking.setPosition(sf::Vector2f(x, y));
        
        player->setColision(player->getDirection(), true);
        //player->hasColided = false;
    }
}


void Block::updateAnimation()
{
    breaking.update();
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

void Block::destroyBlock()
{
    // CHANGE THE ANIMATION TO THE DESTROYING BLOCK
    // AND WHEN THE ANIMATION FINISHES THEN DESTROY THE BLOCK
    if(type.compare("NORMAL")== 0){
        destroyed = true;
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
    if(!destroyed)
    {
        window.draw(sprite);
    } 
    else 
    {
        breaking.draw(window);
    }
}
