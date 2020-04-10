#include "Player.h"

Player::Player(int posx, int posy)
{
    std::cout << "Creating the player" << std::endl;

    hitbox = sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    hitbox.setFillColor(sf::Color::Red);
    x = 0;
    y = 0;

    //hitbox.setOrigin(16/2, 16/2);
    hitbox.setPosition(x, y);

    //movespeed = 16.0/ tilesize; // se mueve una sola vez por bloque, si fuera 32 se movería 2 bloques;
    
    movespeed = 1.5f;


    for(int i = 0; i < 4; i++)
        move[i] = false;
    
    walking = false;

    // hitbox.setPosition(position);

    // SETTING THE ACTUAL ANIMATION
        loadAnimations();
        currentAnim = &run_der;
        currentAnim->setPosition(sf::Vector2f(8, 8));
}

void Player::loadAnimations()
{
    using namespace sf;

    run_up.setFrames(IntRect(16*4, 0, 16, 16), IntRect(16*5, 0, 16, 16));
    run_down.setFrames(IntRect(0,0, 16, 16), IntRect(16, 0, 16, 16));
    run_izq.setFrames(IntRect(16*2, 0, 16, 16), IntRect(16*3, 0, 16, 16));
    run_der.setFrames(IntRect(16*6, 0, 16, 16), IntRect(16*7, 0, 16, 16));

}

void Player::changeAnimation(Animation* newAnimation)
{
    currentAnim = newAnimation;
    currentAnim->setPosition(hitbox.getPosition());
}


Player::~Player()
{
    // Destructor
    delete currentAnim;
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
    if(walking) 
    {

        currentAnim->play();

        if(move[UP]) 
        {
            y -= movespeed;
            changeAnimation(&run_up);

            if(y <= nextspot) {
                y = nextspot;
                walking = false;
                move[UP] = false;
            }
        }

        if(move[DOWN]) 
        {
            y += movespeed;
            changeAnimation(&run_down);

            if(y >= nextspot) {
                y = nextspot;
                walking = false;
                move[DOWN] = false;
            }
        }


        if(move[LEFT]) 
        {
            x -= movespeed;
            changeAnimation(&run_izq);
            if(x <= nextspot) {
                x = nextspot;
                walking = false;
                move[LEFT] = false;
            }
        }

        if(move[RIGHT]) 
        {
            x += movespeed;
            changeAnimation(&run_der);
            if(x >= nextspot) {
                x = nextspot;
                walking = false;
                move[RIGHT] = false;
            }
        }

    } 
    else 
    {   
        currentAnim->stop();
    }
}



void Player::update(float elapsedTime)
{

    setMovement();
    moving(elapsedTime);
    hitbox.setPosition(x, y);
    currentAnim->setPosition(sf::Vector2f(x, y));
    currentAnim->update();

    /*
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        std::cout << "POS ACTUAL: " << hitbox.getPosition().x << ", " << hitbox.getPosition().y << std::endl;
    }
    */
    // Updating the animation
    
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(hitbox);
    currentAnim->draw(window);
}
