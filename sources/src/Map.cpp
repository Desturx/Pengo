#include "Map.h"

Map::Map()
{
    readMap();
    setData();
    loadTextures();
    createSprites();

}

Map::~Map()
{
    for(int i = 0; i < numlayers; i++) {
        for(int j= 0; j < height; j++) {
            delete tileMap[i][j];
        }
        delete tileMap[i];
    }
    delete tileMap;

    for(int i = 0; i < numlayers; i++) {
        for(int j = 0; j < height; j++) {
            for(int z = 0; z < width; z++) {
                delete mapSprite[i][j][z];
            }
            delete mapSprite[i][j];
        }
        delete mapSprite[i];
    }
    delete mapSprite;
}


void Map::readMap()
{
    docum.LoadFile("./resources/maps/mapa1.tmx");
    xmlMap = docum.FirstChildElement("map");
}


void Map::setData()
{
    // Get the data from the generated XML map (generated from tiled)
    xmlMap->QueryIntAttribute("width", &width);
    xmlMap->QueryIntAttribute("height",&height);
    xmlMap->QueryIntAttribute("tilewidth", &tilewidth);
    xmlMap->QueryIntAttribute("tileheight", &tileHeight);

    tileSetImg = xmlMap->FirstChildElement("tileset");

    layer = xmlMap->FirstChildElement("layer");
}

void Map::getLayers()
{
    while(layer) {
        numlayers++;
        layer = layer->NextSiblingElement("layer");
    }
}


void Map::loadTextures()
{
    while(tileSetImg) {
        // Load the texture for the map
        if(!tileSetTexture.loadFromFile("")) {
            std::cerr << "Couldn't load the map texture" << std::endl;
            exit(0);
        }
        tileSetImg = tileSetImg->NextSiblingElement("tileset");
    }

    // Getting the number of layers
    getLayers();

    // Then i go back to the first layer 
    layer = xmlMap->FirstChildElement("layer");

    // ===== Here i could load some objects =====

    // ==========================================

    // Then, again we go back to the first layer
    layer = xmlMap->FirstChildElement("layer");

    tileMap = new int**[numlayers];

    for(int i = 0; i < numlayers; i++) {
        // height of the tilemap
        tileMap[i] = new int*[height];
        for(int j = 0; j < height; j++) {
            // width of the tilemap
            tileMap[i][j] = new int[width];
        } 
    }

    int l = 0;

    while(layer) {
        data = layer->FirstChildElement("data")->FirstChildElement("tile");

        while(data) {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    data->QueryIntAttribute("gid", &tileMap[l][i][j]);
                    data = data->NextSiblingElement("tile");
                }
            }
        }
        layer = layer->NextSiblingElement("layer");
        l++;
    }

}


void Map::createSprites()
{
    mapSprite = new sf::Sprite***[numlayers];

    for(int i = 0; i < numlayers; i++) {
        mapSprite[i] = new sf::Sprite**[height];
        for(int j = 0; j < height; j++) {
            mapSprite[i][j] = new sf::Sprite*[width];
            for(int z = 0; z < width; z++) {
                mapSprite[i][j][z] = new sf::Sprite;
            }
        }
    }

    int cols = tileSetTexture.getSize().x / tilewidth;
    int rows = tileSetTexture.getSize().y / tileHeight;

    tilesetSprite = new sf::Sprite[rows*cols];

    int n = 0;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            tilesetSprite[n].setTexture(tileSetTexture);
            tilesetSprite[n].setTextureRect(sf::IntRect(j*tilewidth, i*tileHeight, tilewidth, tileHeight));
            n++;
        }
    }

    for(int i = 0; i < numlayers; i++) {
        for(int j = 0; j < height; j++) {
            for(int k = 0; k < width; k++) {
                // TO-DO check this line
                gid = tileMap[i][j][k]-1;

                if(gid > 0 && gid < width*height) 
                {
                    mapSprite[i][j][k] = new sf::Sprite(tileSetTexture, tilesetSprite[gid].getTextureRect());
                    mapSprite[i][j][k]->setPosition(k*tilewidth, j*tileHeight);
                } 
                else
                {
                    mapSprite[i][j][k] = NULL;
                }
                

            }
        }
    }
}


void Map::update() 
{

}

void Map::draw(sf::RenderWindow& window)
{
    for(int l = 0; l < numlayers; l++) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if(mapSprite[l][y][x] != NULL) {
                    window.draw(*(mapSprite[l][y][x]));
                }
            }
        }
    }
}




