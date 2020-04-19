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
    }
}

Enemy::~Enemy()
{
    delete actual;
}

void Enemy::update()
{
    chooseDirection();

    if(ready)
    {
        moving();
    }
    hitbox.setPosition(x, y);

}


void Enemy::chooseDirection()
{
    int dir = rand() % 4 + 1;
    int finalX = hitbox.getPosition().x/16;
    int finalY = hitbox.getPosition().y/16;
    if(!canGo[UP])
    {
        while(dir == 1)
        {
            dir = rand() % 4 + 1;
        }
    }
    else if(!canGo[DOWN])
    {
        while(dir == 3)
        {
            dir = rand() % 4 + 1;
        } 

    }
    else if(!canGo[RIGHT])
    {
        while(dir == 2)
        {
            dir = rand() % 4 + 1;
        }

    }
    else if(!canGo[LEFT])
    {
        while (dir == 4)
        {
            dir = rand() % 4 + 1;
        }
    }



    if(!walking)
    {
        dirMoving = dir;
        ready = false;


        if(dir == 1) // moves up
        {
            std::cout << "moves up" << std::endl;
            move[UP] = true;
            walking = true;
            
            //std::cout << "lastY" << lastY << ", actualY: " << finalY << std::endl;
            
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
            
            if(finalY != lastY) 
            {
                canGo[DOWN] = true;
            }
            nextSpot = finalY*16;
            lastY = finalY;
            //std::cout << "Next position: " << finalX << ", " << finalY << std::endl;
        }

        if(dir == 2) // moves rigth
        {
            std::cout << "moves rigth" << std::endl;
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

            if(finalX != lastX)
            {
                canGo[LEFT] = true;
            }

            nextSpot = finalX*16;
            lastX = finalX;
            //std::cout << "Next position: " << finalX << ", " << finalY << std::endl;

        }

        if(dir == 3) // moves down
        {
            std::cout << "moves down" << std::endl;
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

            if(finalY != lastY)
            {
                canGo[UP] = true;
            }
            nextSpot = finalY*16;
            lastY = finalY;
            //std::cout << "Next position: " << finalX << ", " << finalY << std::endl;

        }

        if(dir == 4) // moves left
        {   
            std::cout << "moves left" << std::endl;
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
            
            if(finalX != lastX)
            {
                canGo[RIGHT] = true;
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

            if(y <= nextSpot){
                y = nextSpot;
                walking = false;
                move[UP] = false;
            }
        }
        
        if(move[RIGHT])
        {
            x += movespeed;

            if(x >= nextSpot) {
                x = nextSpot;
                walking = false;
                move[RIGHT] = false;
            }
        }

        if(move[DOWN])
        {
            y += movespeed;

            if(y >= nextSpot) {
                y = nextSpot;
                walking = false;
                move[DOWN] = false;
            }
        }

        if(move[LEFT])
        {
            x -= movespeed;

            if(x <= nextSpot) {
                x = nextSpot;
                walking = false;
                move[LEFT] = false;
            }
        }

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


void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(hitbox);
}
