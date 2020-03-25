#include "Animation.h"

Animation::Animation(char* textureName, int spriteSize, float animationVel) 
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
    sprite.setOrigin(firstF.width/2, firstF.height/2);
}


void Animation::update()
{
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