#include "Map.h"

Map::Map()
{

}

void Map::loadLevel() 
{
    readMap();
    setData();
    loadTextures();
    createSprites();
}


void Map::printData()
{
    using namespace std;

    cout << endl << "Mapa de colisiones:" << endl;
    cout <<  "------------------------" << endl;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            cout << colisions[y][x] << "-";
        }
       cout << endl;
    }
    cout <<  "------------------------" << endl;
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
        if(!tileSetTexture.loadFromFile("./resources/maps/patron.png")) {
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


    colisions = new int*[height];
    for(int i = 0; i < height; i++) {
        colisions[i] = new int[width]; 
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
                colisions[j][k] = 0;
                if(gid > 0 && gid < width*height) 
                {

                    
                    if(gid == 1) 
                    {
                        // COLOCAR LOS SPRITES DE LOS BLOQUES AZULES Y MANDARLOS
                        Block* newBlock = new Block(tileSetTexture, tilesetSprite[gid].getTextureRect(), sf::Vector2f(k*tilewidth, j*tileHeight) );
                        dest_blocks.push_back(newBlock);
                        colisions[j][k] = 1;

                    }
                    else if(gid == 3)
                    {
                        colisions[j][k] = 2;
                        mapSprite[i][j][k] = new sf::Sprite(tileSetTexture, tilesetSprite[gid].getTextureRect());
                        mapSprite[i][j][k]->setPosition(k*tilewidth, j*tileHeight);
                    } 
                    else
                    {
                        colisions[j][k] = 3;
                        mapSprite[i][j][k] = new sf::Sprite(tileSetTexture, tilesetSprite[gid].getTextureRect());
                        mapSprite[i][j][k]->setPosition(k*tilewidth, j*tileHeight);
                    }
                    
                } 
                else
                {
                    mapSprite[i][j][k] = NULL;
                }
                

            }
        }
    }
}

sf::Vector2f Map::getViewPosition()
{
    tinyxml2::XMLElement* object;

    object = xmlMap->FirstChildElement("objectgroup");
    std::string viewLayer; 
    int x = 0; int y = 0;

    while(object) {
        viewLayer = (std::string)object->Attribute("name");
        
        if(viewLayer.compare("view") == 0) {
            object = object->FirstChildElement("object");

            object->QueryIntAttribute("x", &x);
            object->QueryIntAttribute("y", &y);

            break;

        } else {
            object = object->NextSiblingElement("objectgroup");
        }
    }

    return sf::Vector2f(x, y);
}

sf::Vector2f Map::getPlayerPosition()
{
     tinyxml2::XMLElement* object;

    object = xmlMap->FirstChildElement("objectgroup");
    std::string playerPos; 
    int x = 0; int y = 0;

    while(object) {
        playerPos = (std::string)object->Attribute("name");
        
        if(playerPos.compare("playerPosition") == 0) {
            object = object->FirstChildElement("object");

            object->QueryIntAttribute("x", &x);
            object->QueryIntAttribute("y", &y);

            break;

        } else {
            object = object->NextSiblingElement("objectgroup");
        }
    }

    return sf::Vector2f(x, y);
}

void Map::update(Player *player) 
{
    // update for the blocks

    for(unsigned i = 0; i < dest_blocks.size(); i++) {

        float distanceX = player->getPosition().x - dest_blocks.at(i)->getPosition().x;
        float distanceY = player->getPosition().y - dest_blocks.at(i)->getPosition().y;
        float final = sqrt(pow(distanceX, 2)+pow(distanceY, 2));

        if(final <= 16.f && !dest_blocks.at(i)->getMoving()) { // si el bloque no se mueve
            
            dest_blocks.at(i)->update(player);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)) 
            {
                updateColisions(dest_blocks.at(i));
            }
        }
        else if(dest_blocks.at(i)->getMoving()) // si el bloque se está moviendo
        {
            dest_blocks.at(i)->update2();
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        printData();
    }

}


void Map::updateColisions(Block* block)
{
    using namespace std;
                cout << "Fila: " << block->getPosition().y/16 << endl;
                cout << "Columna: " << block->getPosition().y/16 << endl;
                int row = block->getPosition().y/16;
                int col = block->getPosition().x/16;
                int rowFinal = row;
                int colFinal = col;

                colisions[row][col] = 0;

                while(colisions[rowFinal][colFinal] == 0) 
                {
                    rowFinal--;
                    // dependiendo de hacia que posición se tenga que dirigir
                } 

                // dependiendo de hacia que posición vaya sumo o resto
                rowFinal++;
                
                /*
                int movFinalY = rowFinal - row;
                int movFinalX = colFinal - col;
                */
                block->setNextSpot(rowFinal*16);
                colisions[rowFinal][colFinal] = 1;
                //block->setPosition(sf::Vector2f(colFinal*16, rowFinal*16));
}

void Map::draw(sf::RenderWindow& window)
{
    for(int l = 0; l < numlayers; l++) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if(mapSprite[l][y][x] != NULL) {
                    window.draw(*(mapSprite[l][y][x]));
                    //std::cout << "se dibuja" << std::endl;
                }
            }
        }
    }


    for(unsigned i = 0; i < dest_blocks.size(); i++) {
        dest_blocks.at(i)->draw(window);
        // dest_blocks.at(i)->drawGizmo(window);

    }
}




