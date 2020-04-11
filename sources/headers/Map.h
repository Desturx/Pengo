#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml2.h"
#include "Block.h"


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
        

    public:
        Map();
        virtual ~Map();
        void readMap();
        void setData();
        void loadTextures();
        void createSprites();
        void getLayers();
        void creaColisiones();

        void printData();

        void update();
        void draw(sf::RenderWindow& window);


};

