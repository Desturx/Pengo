#include "Enemy.h"


Enemy::Enemy(float posx, float posy) 
{
    hitbox = sf::RectangleShape(sf::Vector2f(16,16));
    x = posx;
    y = posy;
    lastX = x/16;
    lastY = y/16;
    hitbox.setPosition(x, y);
    hitbox.setFillColor(sf::Color::Blue);
    for(int i = 0; i < 4; i++) {
        move[i] = false;
        canGo[i] = true;
        collides[i] = true;
    }

    loadAnimations();

    currentAnim = &eggSpawn;
    currentAnim->setPosition(sf::Vector2f(x, y));
}

Enemy::~Enemy()
{
    //delete currentAnim;
}


void Enemy::loadAnimations()
{
    using namespace sf;

    // RUNNING ANIMATIONS
    run_up.setFrames(IntRect(16*4, 16, 16, 16), IntRect(16*5, 16, 16, 16));
    run_down.setFrames(IntRect(16*0, 16, 16, 16), IntRect(16*1, 16, 16, 16));
    run_left.setFrames(IntRect(16*2, 16, 16, 16), IntRect(16*3, 16, 16, 16));
    run_right.setFrames(IntRect(16*6, 16, 16, 16), IntRect(16*7, 16, 16, 16));


    // EGG ANIMATION
    eggSpawn.setFrames(IntRect(16*0, 0, 16, 16), IntRect(16*5, 0, 16, 16));
    eggSpawn.loopXtimes(2); 

}

void Enemy::kill()
{
    dead = true;
}

void Enemy::changeAnimation(Animation* newAnimation)
{
    if(newAnimation != currentAnim) {
        newAnimation->reset();
        currentAnim = newAnimation;
        currentAnim->setPosition(hitbox.getPosition());
    }
    
}

void Enemy::update()
{
    if(currentAnim == &eggSpawn )
    {
       if(currentAnim->isFinished())
       {
           changeAnimation(&run_down);
       }
    }
    else
    {
        if(!doNothing)
        {
            if(!walking)
            {
                chooseDirection();

            }
            if(walking)
            {
                moving();
                setPosition();
            }
        }
    }
   
    currentAnim->update();

}

void Enemy::setPosition()
{
    hitbox.setPosition(x, y);
    currentAnim->setPosition(sf::Vector2f(x, y));

}

void Enemy::setDir()
{
    int dir = rand() % 4 + 1;

    if(dir == 1)
    {
        if(collides[UP])
        {
            dirMoving = dir;
        }
        else
        {
            dirMoving = 0;
        }
    }
    
    if(dir == 2)
    {
        if(collides[RIGHT])
        {
            dirMoving = dir;

        }
        else
        {
            dirMoving = 0;
        }
    }
    
    if(dir == 3)
    {
        if(collides[DOWN])
        {
            dirMoving = dir;
        }
        else
        {
            dirMoving = 0;
        }
        
    }
    
    if (dir == 4)
    {
        if(collides[LEFT])
        {
            dirMoving = dir;

        }
        else
        {
            dirMoving = 0;
        }
        
    }

    if(!collides[UP] && !collides[DOWN] && !collides[LEFT] && !collides[RIGHT])
    {
        doNothing = true;
    }

    

}

void Enemy::chooseDirection()
{
    int finalX = hitbox.getPosition().x/16;
    int finalY = hitbox.getPosition().y/16;
    
    do
    {
        setDir();
    } while (dirMoving == 0 || doNothing == true);
    

    if(!walking)
    {
        ready = false;
        if(dirMoving == 1) // moves up
        {
            // std::cout << "moves up" << std::endl;
            move[UP] = true;
            walking = true;            
            if(lastY != 1 && finalY != 1)
            {
                while(finalY == lastY)
                {
                    int cant = rand() % 17 + 1;
                    if(finalY- cant <= 0) {
                        finalY = 1;
                    } else {
                        finalY -= cant;
                    }
                } 
            }
            nextSpot = finalY*16;
            lastY = finalY;
        }

        if(dirMoving == 2) // moves rigth
        {
            // std::cout << "moves rigth" << std::endl;
            move[RIGHT] = true;
            walking = true;
            
            if(lastX != 13 && finalX != 13)
            {
                while(finalX == lastX)
                {
                    int cant = rand() % 15 + 1;
                    if(finalX + cant >= 14) {
                        finalX = 13;
                    } else {
                        finalX += cant;
                    }
                }
            }
            nextSpot = finalX*16;
            lastX = finalX;
            //std::cout << "Next position: " << finalX << ", " << finalY << std::endl;

        }

        if(dirMoving == 3) // moves down
        {
            // std::cout << "moves down" << std::endl;
            move[DOWN] = true;
            walking = true;

            if(finalY != 16 && lastY != 16)
            {
                while(finalY == lastY)
                {
                    int cant = rand() % 17 + 1;            
                    if(finalY + cant >= 17) {
                        finalY = 16;
                    } else {
                        finalY += cant;
                    }
                }
                
            }
            nextSpot = finalY*16;
            lastY = finalY;
            //std::cout << "Next position: " << finalX << ", " << finalY << std::endl;

        }

        if(dirMoving == 4) // moves left
        {   
            // std::cout << "moves left" << std::endl;
            move[LEFT] = true;
            walking = true;

            if(finalX != 1 && lastX != 1)
            {
                while(finalX == lastX)
                {
                    int cant = rand() % 15 + 1;
                    if(finalX - cant <= 0) {
                        finalX = 1;
                    } else {
                        finalX -= cant;
                    } 
                }
            }

            nextSpot = finalX*16;
            lastX = finalX;
            //std::cout << "Next position: " << finalX << ", " << finalY << std::endl;

        }

    }
}

void Enemy::moving()
{
    if(walking)
    {
        if(move[UP])
        {
            y -= movespeed;
            changeAnimation(&run_up);
            if(y <= nextSpot){
                y = nextSpot;
                walking = false;
                move[UP] = false;
            }
        }
        
        if(move[RIGHT])
        {
            x += movespeed;
            changeAnimation(&run_right);
            if(x >= nextSpot) {
                x = nextSpot;
                walking = false;
                move[RIGHT] = false;
            }
        }

        if(move[DOWN])
        {
            y += movespeed;
            changeAnimation(&run_down);
            if(y >= nextSpot) {
                y = nextSpot;
                walking = false;
                move[DOWN] = false;
            }
        }

        if(move[LEFT])
        {
            x -= movespeed;
            changeAnimation(&run_left);
            if(x <= nextSpot) {
                x = nextSpot;
                walking = false;
                move[LEFT] = false;
            }
        }

    }
}

void Enemy::setCanGo(int dir, bool value)
{
    if(dir == 1)
    {
        collides[UP] = value;
    }
    else if(dir == 2)
    {
        collides[RIGHT] = value;
    }
    else if(dir == 3)
    {
        collides[DOWN] = value;
    }
    else if(dir == 4)
    {
        collides[LEFT] = value;
    }
}

void Enemy::stopMoving(int next, int dir)
{
    nextSpot = next;
    ready = true;
    //std::cout << "debería parar ahora en: " << next/16 << std::endl;

    if(dir == 1)
    {
        canGo[UP] = false;
    }
    else if(dir == 2)
    {
        canGo[RIGHT] = false;
    }
    else if (dir == 3)
    {
        canGo[DOWN] = false;
    }
    else if (dir == 4)
    {
        canGo[LEFT] = false;
    }
    
    
}

void Enemy::setNextSpot(int next)
{
    nextSpot = next;
}

void Enemy::draw(sf::RenderWindow& window)
{
    //window.draw(hitbox);
    currentAnim->draw(window);
}
