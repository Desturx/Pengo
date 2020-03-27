#include "Player.h"

Player::Player(sf::Vector2f position)
{
    std::cout << "Creating the player" << std::endl;

    hitbox = sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    hitbox.setFillColor(sf::Color::Red);

    x = 0;
    y = 0;

    //movespeed = 16.0/ tilesize; // se mueve una sola vez por bloque, si fuera 32 se movería 2 bloques;
    movespeed = 0.11f;
    for(int i = 0; i < 4; i++)
        move[i] = false;
    
    walking = false;

    // hitbox.setPosition(position);

    // SETTING THE ANIMATIONS
    /*
        ================= INFO ==================
        posx = X position for the top left corner
        posy = Y position for the top left corner
        width = width of the sprite
        heigth = heigth of the sprite
        =========================================

        run.setFrames(sf::IntRect(posX,posY, width, height))
    */


    // SETTING THE ACTUAL ANIMATION
    /*
        currentAnim = &run;
        currentAnim->setPosition(pos);
    */ 
}


Player::~Player()
{
    // Destructor
}

void Player::setMovement() 
{   

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
   {
       if(!walking) 
       {
           nextspot = y - tilesize;
           move[UP] = true;
           walking = true;
       }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
   {
       if(!walking) 
       {
           nextspot = y + tilesize;
           move[DOWN] = true;
           walking = true;
       }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
   {
       if(!walking) 
       {
           nextspot = x - tilesize;
           move[LEFT] = true;
           walking = true;
       }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
   {
       if(!walking) 
       {
           nextspot = x + tilesize;
           move[RIGHT] = true;
           walking = true;
       }
   }

}

void Player::moving(float elapsedTime) 
{
    if(walking) {
        if(move[UP]) 
        {
            y -= movespeed*elapsedTime;

            if(y <= nextspot) {
                y = nextspot;
                walking = false;
                move[UP] = false;
            }
        }

        if(move[DOWN]) 
        {
            y += movespeed*elapsedTime;

            if(y >= nextspot) {
                y = nextspot;
                walking = false;
                move[DOWN] = false;
            }
        }


        if(move[LEFT]) 
        {
            x -= movespeed*elapsedTime;

            if(x <= nextspot) {
                x = nextspot;
                walking = false;
                move[LEFT] = false;
            }
        }

        if(move[RIGHT]) 
        {
            x += movespeed*elapsedTime;

            if(hitbox.getPosition().x >= nextspot) {
                hitbox.setPosition(nextspot, hitbox.getPosition().y);
                walking = false;
                move[RIGHT] = false;
            }
        }

    }
}


void Player::update(float elapsedTime)
{

    setMovement();
    moving(elapsedTime);
    hitbox.setPosition(x, y);


    // Updating the animation
    //currentAnim->update()
    

}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(hitbox);
    // currentAnim->draw(window);
}
