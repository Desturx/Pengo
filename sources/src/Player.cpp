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
        currentAnim = &run_right;
        currentAnim->setPosition(sf::Vector2f(8, 8));
}

void Player::loadAnimations()
{
    using namespace sf;

    // RUNNING ANIMATIONS
    run_up.setFrames(IntRect(16*4, 0, 16, 16), IntRect(16*5, 0, 16, 16));
    run_down.setFrames(IntRect(0,0, 16, 16), IntRect(16, 0, 16, 16));
    run_left.setFrames(IntRect(16*2, 0, 16, 16), IntRect(16*3, 0, 16, 16));
    run_right.setFrames(IntRect(16*6, 0, 16, 16), IntRect(16*7, 0, 16, 16));

    // PUSHING ANIMATIONS
    push_left.setFrames(IntRect(16*2, 16, 16, 16), IntRect(16*3, 16, 16, 16));
    push_left.loopXtimes(1);


}

void Player::changeAnimation(Animation* newAnimation)
{
    if(newAnimation != currentAnim) {
        newAnimation->reset();
        currentAnim = newAnimation;
        currentAnim->setPosition(hitbox.getPosition());
    }
    
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
       if(!walking && !playingAnimation) 
       {
           nextspot = y - tilesize;
           move[UP] = true;
           lastPosition = "UP";
           walking = true;
       }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
   {
       if(!walking && !playingAnimation) 
       {
           nextspot = y + tilesize;
           move[DOWN] = true;
           lastPosition = "DOWN";
           walking = true;
       }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
   {
       if(!walking && !playingAnimation) 
       {
           nextspot = x - tilesize;
           move[LEFT] = true;
           lastPosition = "LEFT";
           walking = true;
       }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
   {
       if(!walking && !playingAnimation) 
       {
           nextspot = x + tilesize;
           move[RIGHT] = true;
           lastPosition = "RIGHT";
           walking = true;
       }
   }

}

void Player::moving(float elapsedTime) 
{
    if(walking) // if the player is moving
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
            changeAnimation(&run_left);
            if(x <= nextspot) {
                x = nextspot;
                walking = false;
                move[LEFT] = false;
            }
        }

        if(move[RIGHT]) 
        {
            x += movespeed;
            changeAnimation(&run_right);
            if(x >= nextspot) {
                x = nextspot;
                walking = false;
                move[RIGHT] = false;
            }
        }

    } 
    else // if the player isn't moving 
    {   
        currentAnim->stop();

    }
}

void Player::update(float elapsedTime)
{

    setMovement();
    moving(elapsedTime);

    
    if(playingAnimation) 
    {
        currentAnim->play();
        if(currentAnim->isFinished()) {
            playingAnimation = false;
        }
    }


    if(!walking) {
        // PARA QUE SE CHOQUE CON LOS BLOQUES Y LOS EMPUJE
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

            if(lastPosition == "LEFT" && !playingAnimation) 
            {
                changeAnimation(&push_left);
                playingAnimation = true;
            } 
            else if(lastPosition == "RIGHT" && !playingAnimation)
            {
                /*
                changeAnimation(&push_right);
                playingAnimation = true;
                */
               
            }

        }
    }

    hitbox.setPosition(x, y);
    currentAnim->setPosition(sf::Vector2f(x, y));
    currentAnim->update();
    
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(hitbox);
    currentAnim->draw(window);
}
