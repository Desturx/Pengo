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
This constructor is only for the walls
*/
Block::Block(sf::Vector2f position,sf::Vector2f size, std::string name)
{
    type = "WALL";

    hitbox = sf::RectangleShape(size);
    hitbox.setFillColor(sf::Color::Red);
    
    if(name.compare("left") == 0)
    {
        hitbox.setPosition(position.x-16, position.y);
        using namespace sf;
        wallSide.setFrames(IntRect(8*0, 0, 8, 256), IntRect(8*1, 0, 8, 256));
        wallSide.loopXtimes(4);
        wallSide.setPosition(Vector2f(position.x, position.y - 8));
        animationUsed = "side";

    }
    else if(name.compare("rigth") == 0)
    {
        hitbox.setPosition(position.x, position.y);
        using namespace sf;
        wallSide.setFrames(IntRect(8*0, 0, 8, 256), IntRect(8*1, 0, 8, 256));
        wallSide.loopXtimes(4);
        wallSide.setPosition(Vector2f(position.x, position.y - 8));
        animationUsed = "side";

    }
    else if (name.compare("top") == 0)
    {
        hitbox.setPosition(position.x, position.y);
        //std::cout << "entra aqui" << std::endl;
        using namespace sf;
        wallTop.setFrames(IntRect(224*0, 0, 224, 8), IntRect(224*1, 0, 224, 8));
        wallTop.loopXtimes(4);
        wallTop.setPosition(Vector2f(position.x - 8, position.y));
        animationUsed = "top";
        
    }
    else if (name.compare("bot") == 0)
    {
        hitbox.setPosition(position.x, position.y + 16);
        using namespace sf;
        wallTop.setFrames(IntRect(224*0, 0, 224, 8), IntRect(224*1, 0, 224, 8));
        wallTop.loopXtimes(4);
        wallTop.setPosition(Vector2f(position.x - 8, position.y));
        animationUsed = "top";

    }
}

void Block::restartWallAnimation()
{
    animateWall = false;
    if(animationUsed.compare("top") == 0)
    {
        wallTop.reset();
    }
    else
    {
        wallSide.reset();   
    }
    
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
        if(type.compare("WALL") == 0)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            {
                if(!player->isMoving())
                {
                    if(player->getDirection().compare("UP")== 0)
                    {
                        startWallAnimation();
                    }
                }
            }
        }
    }
    
    if(hitbox.getGlobalBounds().intersects(player->bottomColision().getGlobalBounds())) 
    {
        player->setColision("DOWN", false);
        player->hasColided = true;
        dirIsColliding = "DOWN";
        if(type.compare("WALL") == 0)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            {
                if(!player->isMoving())
                {
                    if(player->getDirection().compare("DOWN")== 0)
                    {
                        startWallAnimation();
                    }
                }
            }
        }
    } 
    
    if(hitbox.getGlobalBounds().intersects(player->leftColision().getGlobalBounds())) 
    {
        player->setColision("LEFT", false);
        player->hasColided = true;
        dirIsColliding = "LEFT";
        if(type.compare("WALL") == 0)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            {
                if(!player->isMoving())
                {
                    if(player->getDirection().compare("LEFT")== 0)
                    {
                        startWallAnimation();
                    }
                }
            }
        }
    }
    
    if(hitbox.getGlobalBounds().intersects(player->rightColision().getGlobalBounds())) 
    {
        player->setColision("RIGHT", false);
        player->hasColided = true;
        dirIsColliding = "RIGHT";
        if(type.compare("WALL") == 0)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            {
                if(!player->isMoving())
                {
                    if(player->getDirection().compare("RIGHT")== 0)
                    {
                        startWallAnimation();
                    }
                }
            }
        }
    }



}

void Block::update2(Player *player)
{

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

void Block::updateWallAnimation()
{
    if(animationUsed.compare("top") == 0)
    {
        wallTop.update();
    }
    else if(animationUsed.compare("side") == 0)
    {
        wallSide.update();
    }
}


void Block::startWallAnimation()
{
    animateWall = true;
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

bool Block::isWallFinished()
{
    bool res = false;
    if(animationUsed.compare("top") == 0)
    {
        res = wallTop.isFinished();
    }
    else if(animationUsed.compare("side") == 0)
    {
        res = wallSide.isFinished();
    }

    return res;

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

    if(type.compare("WALL")== 0)
    {
        if(animateWall)
        {
            if(animationUsed.compare("top") == 0)
            {
                wallTop.draw(window);
            }
            if(animationUsed.compare("side") == 0)
            {
                wallSide.draw(window);
            }
        }
        else
        {
            //window.draw(hitbox);
        }
        
    }


}
