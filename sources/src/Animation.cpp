#include "Animation.h"


Animation::Animation(std::string textureName, int spriteSize, float animationVel) 
{
    if(!texture.loadFromFile(textureName)) {
        std::cout << "FAIL LOADING TEXTURE: " << textureName << std::endl;
    }
    sprSize = spriteSize;
    animVel = animationVel;
}


Animation::~Animation() 
{
    // Destructor
}

void Animation::setFrames(sf::IntRect firstFrame, sf::IntRect lastFrame)
{
    firstF = firstFrame;
    lastF = lastFrame;
    actualF = firstFrame;

    sprite = sf::Sprite(texture, actualF);
    sprite.setOrigin(0, 0);
}


void Animation::update()
{
    //std::cout << "se llama al update" << std::endl;
    float delta = clock.getElapsedTime().asSeconds();
    if(delta >= animVel) {
        clock.restart();
        if(actualF.left == lastF.left) {
            actualF.left = firstF.left;
        } else {
            actualF.left += sprSize;
        }

        sprite.setTextureRect(actualF);
    }

    // Moving the sprite with the character
    // sprite.move(movement*mTime);
}

void Animation::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Animation::draw(sf::RenderWindow& window) 
{
    //std::cout << "se llama al dibujado" << std::endl;
    window.draw(sprite);
}
