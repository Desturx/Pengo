#include "Player.h"

Player::Player(int posx, int posy)
{
    std::cout << "Creating the player" << std::endl;

    hitbox = sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    hitbox.setFillColor(sf::Color::Red);
    x = posx;
    y = posy;

    hitbox.setPosition(x, y);
    movespeed = 1.5f;


    for(int i = 0; i < 4; i++)
        move[i] = false;
    
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
    push_left.loopXtimes(1);

    push_right.setFrames(IntRect(16*6, 16, 16, 16), IntRect(16*7, 16, 16, 16));
    push_right.loopXtimes(1);

    push_up.setFrames(IntRect(16*4, 16, 16, 16), IntRect(16*5, 16, 16, 16));
    push_up.loopXtimes(1);

    push_down.setFrames(IntRect(16*0, 16, 16, 16), IntRect(16*1, 16, 16, 16));
    push_down.loopXtimes(1);




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
        pushingBlocks();
    }   

    hitbox.setPosition(x, y);
    currentAnim->setPosition(sf::Vector2f(x, y));
    currentAnim->update();
    moveColisions();

    // checkColisions(blocks);

    
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



/*
void Player::checkColisions(std::vector<Block*> blocks)
{
    
    for(int i = 0; i < 4; i++){
        for(unsigned j = 0; j < blocks.size(); j++) {
            if(colisions[i].getGlobalBounds().intersects(blocks.at(j)->getGlobalBounds()))
            {
                std::cout << "ESTÁ'COLISIONANDO EN ALGÚN LAO" << std::endl;
            }

        }
    } 
}
*/

void Player::pushingBlocks()
{
    // PARA QUE SE CHOQUE CON LOS BLOQUES Y LOS EMPUJE
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

        if(lastPosition == "LEFT" && !playingAnimation) 
        {
            changeAnimation(&push_left);
            playingAnimation = true;
        } 
        else if(lastPosition == "RIGHT" && !playingAnimation)
        {
            
            changeAnimation(&push_right);
            playingAnimation = true;
        }
        else if(lastPosition == "UP" && !playingAnimation)
        {
            changeAnimation(&push_up);
            playingAnimation = true;
        }
        else if(lastPosition == "DOWN" && !playingAnimation)
        {
            changeAnimation(&push_down);
            playingAnimation = true;            
        }
    }
}

void Player::draw(sf::RenderWindow& window)
{
    //window.draw(hitbox);
    currentAnim->draw(window);
    for(int i = 0; i < 4; i++) {
        window.draw(colisions[i]);
    }

}
