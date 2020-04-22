#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Animation.h"

class Block {
    public:
        Block(sf::Texture &texture,sf::IntRect tamSprite, sf::Vector2f position, std::string blockType);
        Block(sf::Vector2f position, sf::Vector2f size, std::string name);
        virtual ~Block();
        void update(Player *player);
        void update2(Player *player);
        void draw(sf::RenderWindow &window);
        void drawGizmo(sf::RenderWindow &window);
        sf::FloatRect getGlobalBounds();
        sf::Vector2f getPosition();
        void setNextSpot(int nextSpot, std::string direction);
        void destroyBlock();
        bool getMoving(){return isMoving;}
        bool getDestroyed(){return destroyed;};
        std::string getDirIsColliding(){return dirIsColliding;};
        std::string getType(){return type;};
        
        void updateAnimation();
        void updateWallAnimation();
        void startWallAnimation();
        bool isAnimationFinished(){return breaking.isFinished();};
        bool isWallFinished();
        bool isAnimatedWall(){return animateWall;};
        void restartWallAnimation();
    private:
        sf::RectangleShape hitbox;
        sf::Sprite sprite;
        bool isMoving  = false;
        bool destroyed = false;
        bool animateWall = false;
        std::string animationUsed;
        int x, y, nextSpot;
        float moveSpeed = 4.f;
        std::string type;
        std::string dir;
        std::string dirIsColliding;

        //Animation *current;
        std::string textureSrc = "./resources/destroyBlock.png";
        // Animation normal = Animation(textureSrc, 16, 0.15f);
        Animation breaking = Animation(textureSrc, 16, 0.15f);
        Animation wallSide = Animation("./resources/wall.png", 8, 0.15f);
        Animation wallTop = Animation("./resources/waltop.png", 224, 0.15f);
};