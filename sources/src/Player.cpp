#include "Player.h"

Player::Player(sf::Vector2f position)
{
    std::cout << "Creating the player" << std::endl;

    hitbox = sf::RectangleShape(sf::Vector2f(16.f, 16.f));
    hitbox.setPosition(position);

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

void Player::update(float elapsedTime)
{
    // Updating the animation
    //currentAnim->update()
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(hitbox);
    // currentAnim->draw(window);
}
