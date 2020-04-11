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

    if(delta >= animVel && isPlaying && !finished) {
        clock.restart();

        if(!loop) {

            if(actualF.left != lastF.left) {
                actualF.left += sprSize;
            } else {
                finished = true;
            }

        } else if(loop) {
            if(loopNumbers > 0) {
                // std::cout << "Se ha hecho: " << times << std::endl;
                if(times <= loopNumbers) {
                    if(actualF.left == lastF.left) {
                        actualF.left = firstF.left;
                        times++;
                    } else {
                        actualF.left += sprSize;
                    }
                } else {
                    finished = true;
                }
            } else {
                if(actualF.left == lastF.left) {
                    actualF.left = firstF.left;
                } else {
                    actualF.left += sprSize;
                }
            }
            sprite.setTextureRect(actualF);
        }

        
    }

    // Moving the sprite with the character
    // sprite.move(movement*mTime);
}

void Animation::noLoop() 
{
    loop = false;
}

void Animation::play()
{
    isPlaying = true;
}

void Animation::stop()
{
    isPlaying = false;
}

bool Animation::isFinished() 
{
    return finished;
}

void Animation::loopXtimes(int timesToLoop)
{
    loopNumbers = timesToLoop;
}

void Animation::reset()
{
    times = 0;
    finished = false;
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
