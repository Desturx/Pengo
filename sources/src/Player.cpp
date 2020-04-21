#include "Player.h"

Player::Player(int posx, int posy)
{
    std::cout << "Creating the player" << std::endl;

    hitbox = sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    hitbox.setFillColor(sf::Color::Red);
    x = posx;
    y = posy;

    hitbox.setPosition(x, y);
    movespeed = 2.f;


    for(int i = 0; i < 4; i++) {
        move[i] = false;
        canMove[i] = true;
    }
    
    walking = false;

    // SETTING THE ACTUAL ANIMATION
    loadAnimations();

    for(unsigned col = 0; col < 4; col++) {
        colisions[col] = sf::RectangleShape(sf::Vector2f(16,16));
        colisions[col].setFillColor(sf::Color::Green);
    }

    colisions[UP].setPosition(x, y - 16);
    colisions[DOWN].setPosition(x, y + 16);
    colisions[RIGHT].setPosition(x + 16, y);
    colisions[LEFT].setPosition(x - 16, y);
    

    currentAnim = &run_down;
    currentAnim->setPosition(sf::Vector2f(8, 8));
}

void Player::loadAnimations()
{
    using namespace sf;

    // RUNNING ANIMATIONS
    run_up.setFrames(IntRect(16*4, 0, 16, 16), IntRect(16*5, 0, 16, 16));
    run_down.setFrames(IntRect(16*0,0, 16, 16), IntRect(16*1, 0, 16, 16));
    run_left.setFrames(IntRect(16*2, 0, 16, 16), IntRect(16*3, 0, 16, 16));
    run_right.setFrames(IntRect(16*6, 0, 16, 16), IntRect(16*7, 0, 16, 16));

    // PUSHING ANIMATIONS
    push_left.setFrames(IntRect(16*2, 16, 16, 16), IntRect(16*3, 16, 16, 16));
    push_left.loopXtimes(3);

    push_right.setFrames(IntRect(16*6, 16, 16, 16), IntRect(16*7, 16, 16, 16));
    push_right.loopXtimes(3);

    push_up.setFrames(IntRect(16*4, 16, 16, 16), IntRect(16*5, 16, 16, 16));
    push_up.loopXtimes(3);

    push_down.setFrames(IntRect(16*0, 16, 16, 16), IntRect(16*1, 16, 16, 16));
    push_down.loopXtimes(3);




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
        lastPosition = "UP";

        if(!walking && !playingAnimation) {
            changeAnimation(&run_up);
        }

        if(!walking && !playingAnimation && canMove[UP]) 
        {
            nextspot = y - tilesize;
            move[UP] = true;
            walking = true;
        }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
   {    
        lastPosition = "DOWN";

        if(!walking && !playingAnimation) {
            changeAnimation(&run_down);
        }

        if(!walking && !playingAnimation  && canMove[DOWN]) 
        {
            nextspot = y + tilesize;
            move[DOWN] = true;
            walking = true;
        }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
   {
        lastPosition = "LEFT";

        if(!walking && !playingAnimation) {
            changeAnimation(&run_left);
        }

        if(!walking && !playingAnimation && canMove[LEFT]) 
        {
            nextspot = x - tilesize;
            move[LEFT] = true;
            walking = true;
        }
   }

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
   {
        lastPosition = "RIGHT";

        if(!walking && !playingAnimation) {
            changeAnimation(&run_right);
        }

        if(!walking && !playingAnimation && canMove[RIGHT]) 
        {
            nextspot = x + tilesize;
            move[RIGHT] = true;
            walking = true;
        }
   }

}

void Player::moving(float elapsedTime) 
{
    if(walking) // if the player is moving
    {
        currentAnim->play();

        if(move[UP] && canMove[UP]) 
        {
            y -= movespeed;
            //changeAnimation(&run_up);

            if(y <= nextspot) {
                y = nextspot;
                walking = false;
                move[UP] = false;
            }
        }

        if(move[DOWN] && canMove[DOWN]) 
        {
            y += movespeed;
            //changeAnimation(&run_down);

            if(y >= nextspot) {
                y = nextspot;
                walking = false;
                move[DOWN] = false;
            }
        }


        if(move[LEFT] && canMove[LEFT]) 
        {
            x -= movespeed;
            //changeAnimation(&run_left);
            if(x <= nextspot) {
                x = nextspot;
                walking = false;
                move[LEFT] = false;
            }
        }

        if(move[RIGHT] && canMove[RIGHT]) 
        {
            x += movespeed;
            //changeAnimation(&run_right);
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
        // pushingBlocks();
    } else {
        if(hasColided) {
            for(int i = 0; i < 4; i++) {
                canMove[i] = true;
            }
            hasColided = false;
        }

    }
    //hitbox.move(x*elapsedTime, y*elapsedTime);
    hitbox.setPosition(x, y);
    currentAnim->setPosition(sf::Vector2f(x, y));
    currentAnim->update();
    moveColisions();

    //std::cout << "se puede mover?:" << canMove[UP] << std::endl;
    
}

void Player::moveColisions()
{
    colisions[UP].setPosition(x, y - 16);
    colisions[DOWN].setPosition(x, y + 16);
    colisions[RIGHT].setPosition(x + 16, y);
    colisions[LEFT].setPosition(x - 16, y);
}

sf::Vector2f Player::getPosition()
{
    return hitbox.getPosition();
}

sf::RectangleShape Player::topColision()
{  
    return colisions[UP];
}

sf::RectangleShape Player::bottomColision()
{  
    return colisions[DOWN];
}

sf::RectangleShape Player::leftColision()
{  
    return colisions[LEFT];
}

sf::RectangleShape Player::rightColision()
{  
    return colisions[RIGHT];
}

/*
Sets the value of the desired colision (UP, DOWN, LEFT, RIGHT)
*/
void Player::setColision(std::string dir, bool value)
{
    if(dir.compare("UP") == 0) 
    {
        canMove[UP] = value;
    }
    else if(dir.compare("DOWN") == 0)
    {
        canMove[DOWN] = value;
    }
    else if(dir.compare("LEFT") == 0)
    {
        canMove[LEFT] = value;
    }
    else if(dir.compare("RIGHT") == 0)
    {
        canMove[RIGHT] = value;
    }

}

void Player::pushingBlocks(std::string direction)
{
    // PARA QUE SE CHOQUE CON LOS BLOQUES Y LOS EMPUJE

    if(direction == "LEFT" && !playingAnimation) 
    {
        changeAnimation(&push_left);
        playingAnimation = true;
    } 
    else if(direction == "RIGHT" && !playingAnimation)
    {
        
        changeAnimation(&push_right);
        playingAnimation = true;
    }
    else if(direction == "UP" && !playingAnimation)
    {
        changeAnimation(&push_up);
        playingAnimation = true;
    }
    else if(direction == "DOWN" && !playingAnimation)
    {
        changeAnimation(&push_down);
        playingAnimation = true;            
    }
}

void Player::draw(sf::RenderWindow& window)
{
    //window.draw(hitbox);
    currentAnim->draw(window);
    
    /*
    for(int i = 0; i < 4; i++) {
        window.draw(colisions[i]);
    }
    */

}
