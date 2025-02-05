#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml2.h"
#include "Block.h"
#include "Enemy.h"
class Player;

class Map {
    private:
        int width, height;
        int tilewidth, tileHeight;
        int gid;        
        
        tinyxml2::XMLDocument docum;
        tinyxml2::XMLElement* xmlMap;
        tinyxml2::XMLElement* tileSetImg;
        tinyxml2::XMLElement* data;
        tinyxml2::XMLElement* layer;

        std::string imageFile;
        sf::Texture tileSetTexture;

        int numlayers = 0;
        int*** tileMap;

        sf::Sprite* tilesetSprite;
        sf::Sprite**** mapSprite;

        std::vector<Block*> dest_blocks;
        int** colisions;
        
        std::vector<Enemy*> enemies;
        int playerLifes = 3;
        int levelLoaded = 0;
        int totalEnemies = 3;

        
    public:
        Map();
        virtual ~Map();
        void loadLevel(int lvl);

        void readMap(int lvl);
        void setData();
        void loadTextures();
        void createSprites();
        void getLayers();
        void creaColisiones();
        void printData();
        void updateColisions(Block *block, std::string direction);
        void checkEnemyColisions(Enemy *e);
        void checkDirection(Enemy *e);
        void checkNextSpot(Enemy *e);
        void subtractLife();
        sf::Vector2f getViewPosition();
        sf::Vector2f getPlayerPosition();
        void getWalls();
        void createEnemy();
        int getLvlLoaded(){return levelLoaded;};
        int getPlayerLifes(){return playerLifes;};
        int getTotalEnemies(){return totalEnemies;};
        int getEnemiesInScreen(){return enemies.size();};
        void update(Player *player);
        void draw(sf::RenderWindow& window);


};

