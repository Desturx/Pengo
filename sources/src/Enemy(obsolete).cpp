#include "Enemy.h"


Enemy::Enemy(float posx, float posy) 
{
    hitbox = sf::RectangleShape(sf::Vector2f(16,16));
    x = posx;
    y = posy;
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

void Enemy::setDir()
{
    int dir = rand() % 4 + 1;

    if(dirMov == 1)
    {
        if(canGo[UP])
        {
            move[UP] = true;
            dirMov = dir;
            walking = true;
        }
        else
        {
            dirMov = 0;
        }
    }
    
    if(dir == 2)
    {
        if(canGo[RIGHT])
        {
            move[RIGHT] = true;
            dirMov = dir;
            walking = true;

        }
        else
        {
            dirMov = 0;
        }
    }
    
    if(dir == 3)
    {
        if(canGo[DOWN])
        {
            move[DOWN] = true;
            dirMov = dir;
            walking = true;
        }
        else
        {
            dirMov = 0;
        }
        
    }
    
    if (dir == 4)
    {
        if(canGo[LEFT])
        {
            move[LEFT] = true;
            dirMov = dir;
            walking = true;

        }
        else
        {
            dirMov = 0;
        }
        
    }

}

void Enemy::setCanGo(int dir, bool value)
{
    if(dir == 1)
    {
        canGo[UP] = value;
    }
    else if(dir == 2)
    {
        canGo[RIGHT] = value;
    }
    else if(dir == 3)
    {
        canGo[DOWN] = value;
    }
    else if(dir == 4)
    {
        canGo[LEFT] = value;
    }
}

void Enemy::stopMoving(int dir)
{

    if(dir == 1)
    {
        move[UP] = false;
    }
    else if (dir == 2)
    {
        move[RIGHT] = false;
    }
    else if (dir == 3)
    {
        move[DOWN] = false;
    }
    else if (dir == 4)
    {
        move[LEFT] = false;
    }
    
    
}

void Enemy::moving()
{
    if(move[UP])
    {
        y-= movespeed;

        if(y >= nextSpot)
        {
            y = nextSpot;
            move[UP] = false;
            dirMov = 0;
            walking = false;
        }
    }

    if(move[DOWN])
    {
        y+= movespeed;
        if(y <= nextSpot)
        {
            y = nextSpot;
            move[DOWN] = false;
            dirMov = 0;
            walking = false;
        }
    }

    if(move[LEFT])
    {
        x-= movespeed;
        
        if(x <= nextSpot)
        {
            x = nextSpot;
            move[LEFT] = false;
            dirMov = 0;
            walking = false;
        }
    }

    if(move[RIGHT])
    {
        x+= movespeed;

        if(x >= nextSpot)
        {
            x = nextSpot;
            move[RIGHT] = false;
            dirMov = 0;
            walking = false;
        }
    }
}

void Enemy::setNextSpot(int spot)
{
    nextSpot = spot;
    walking = true;
}

void Enemy::setPosition()
{
    hitbox.setPosition(x, y);
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(hitbox);
}
