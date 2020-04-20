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

    Enemy* enemy = new Enemy(6*16, 5*16);
    // Enemy* enemy2 = new Enemy(2*16, 8*16);
    enemies.push_back(enemy);
    // enemies.push_back(enemy2);

    std::cout << "width del mapa: " << width << std::endl;
    std::cout << "heigth del mapa: " << height<< std::endl;
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
                        Block* newBlock = new Block(tileSetTexture, tilesetSprite[gid].getTextureRect(), sf::Vector2f(k*tilewidth, j*tileHeight), "NORMAL" );
                        dest_blocks.push_back(newBlock);
                        colisions[j][k] = 1;

                    }
                    else if(gid == 3)
                    {
                        colisions[j][k] = 2;
                        Block* newBlock = new Block(tileSetTexture, tilesetSprite[gid].getTextureRect(), sf::Vector2f(k*tilewidth, j*tileHeight), "SPECIAL");
                        dest_blocks.push_back(newBlock);
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

        if(!dest_blocks.at(i)->getDestroyed())
        {
            float distanceX = player->getPosition().x - dest_blocks.at(i)->getPosition().x;
            float distanceY = player->getPosition().y - dest_blocks.at(i)->getPosition().y;
            float final = sqrt(pow(distanceX, 2)+pow(distanceY, 2));

            if(final <= 16.f && !dest_blocks.at(i)->getMoving()) { // si el bloque no se mueve
                dest_blocks.at(i)->update(player);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
                {
                    if(!player->isMoving()) 
                    {
                        if(player->getDirection().compare(dest_blocks.at(i)->getDirIsColliding())== 0)
                        {
                            updateColisions(dest_blocks.at(i), player->getDirection());
                            player->pushingBlocks(player->getDirection());
                        }
                    }
                    
                }
            }
            else if(dest_blocks.at(i)->getMoving()) // si el bloque se está moviendo
            {
                dest_blocks.at(i)->update2(player);
            }

            // TO PUT THE COLISION IN THE RIGTH PLACE(JUST IN CASE)
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)) 
            {
                for(int i = 0; i < height; i ++) {
                    for(int j = 0; j < width; j++) {
                        colisions[i][j] = 0;
                    }
                }
                int row = dest_blocks.at(i)->getPosition().y/16;
                int col = dest_blocks.at(i)->getPosition().x/16;
                colisions[row][col] = 1;

            }
        }
        else
        {   
            dest_blocks.at(i)->updateAnimation();

            if(dest_blocks.at(i)->getDirIsColliding().compare(player->getDirection()) == 0)
            {
                if(dest_blocks.at(i)->isAnimationFinished())
                {
                    int row = dest_blocks.at(i)->getPosition().y/16;
                    int col = dest_blocks.at(i)->getPosition().x/16;
                    colisions[row][col] = 0;
                    player->setColision(player->getDirection(), true);
                    delete dest_blocks.at(i);
                    dest_blocks.erase(dest_blocks.begin()+i);
                    
                }
                
            }

        }
        
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        printData();
    }

    // Update for the enemies
    for(unsigned i = 0; i < enemies.size(); i++) {
       /*
       (misma técnica que cuando empujo los bloques)
       0º- comprobar en que direcciones se puede mover.
       (si pruebo diviendo en pares las direcciones??)
       1º- seleccionar una direccion a la que moverse
       2º- seleccionar cantidad de bloques que se va a mover
       3º- comprobar si hay algún bloque en el camino,
           si lo hay, esa será su pos final.
       4º- moverlo a esa posición
       */

        
        
        // 0º- comprobar en que direcciones se puede mover.
        checkDirection(enemies.at(i));
        
        // 1º- seleccionar una direccion a la que moverse
        
        if(!enemies.at(i)->getWalking())
        {
            do
            {
                enemies.at(i)->setDir();
            } while (enemies.at(i)->getDir() == 0);

            positionsMoved(enemies.at(i));
        }
        
        // 2º- seleccionar cantidad de bloques que se va a mover
        // 3º- comprobar si hay algún bloque en el camino, si lo hay, esa será su pos final.


        enemies.at(i)->moving();

        enemies.at(i)->setPosition();

    }

}

void Map::positionsMoved(Enemy* e)
{
    int cant = rand() % 5 + 1;
    int row = e->getPosition().y/16;
    int col = e->getPosition().x/16;

    int finalRow = row;
    int finalCol = col;

    if(e->getDir() == 1) // moves up
    {
        bool collides = false;
        if(row - cant <= 0)
        {
            finalRow = 1;
        }
        else
        {
            finalRow-=cant;
        }
        
        // Comprobamos si hay algun bloque por el camino
        while(row > finalRow)
        {
            if(colisions[row][col] != 0)
            {
                collides = true;
                break;
            }
            else
            {
                row --;
            }
        }

        if(collides)
        {
            e->setNextSpot((row+1)*16);
        }
        else
        {
            e->setNextSpot((finalRow)*16);
        }
    }
    else if(e->getDir() == 2)// moves rigth
    {
        bool collides = false;
        if(col + cant >= 14)
        {
            finalCol = 13;
        }
        else
        {
            finalCol += cant;
        }
        
         while(col < finalCol)
        {
            if(colisions[row][col] != 0)
            {
                collides = true;
                break;
            }
            else
            {
                col ++;
            }
        }

        if(collides)
        {
            e->setNextSpot((col-1)*16);
        }
        else
        {
            e->setNextSpot((finalCol)*16);
        }
    }
    else if (e->getDir() == 3) // moves down
    {
        bool collides = false;
        if(row + cant >= 16)
        {
            finalRow = 15;
        }
        else
        {
            finalRow+=cant;
        }
        
        // Comprobamos si hay algun bloque por el camino
        while(row < finalRow)
        {
            if(colisions[row][col] != 0)
            {
                collides = true;
                break;
            }
            else
            {
                row ++;
            }
        }

        if(collides)
        {
            e->setNextSpot((row-1)*16);
        }
        else
        {
            e->setNextSpot((finalRow)*16);
        }
    }
    else if(e->getDir() == 4) // moves left
    {
        bool collides = false;
        if(col - cant <= 0)
        {
            finalCol = 1;
        }
        else
        {
            finalCol -= cant;
        }
        
         while(col > finalCol)
        {
            if(colisions[row][col] != 0)
            {
                collides = true;
                break;
            }
            else
            {
                col ++;
            }
        }

        if(collides)
        {
            e->setNextSpot((col+1)*16);
        }
        else
        {
            e->setNextSpot((finalCol)*16);
        }
    }
    
    

}


void Map::updateColisions(Block* block, std::string direction)
{
    using namespace std;

    int row = block->getPosition().y/16;
    int col = block->getPosition().x/16;
    int rowFinal = row;
    int colFinal = col;
    colisions[rowFinal][colFinal] = 0;

    if(direction.compare("UP") == 0) {
        while(colisions[rowFinal][colFinal] == 0) 
        {
            rowFinal--;
        } 
        rowFinal++;

        if(row == rowFinal) 
        { // if the position isn't modified it has to break
            if(block->getType().compare("NORMAL") == 0) {
                block->destroyBlock();
            }
        } 
        else 
        {// else it can move to the next spot
            block->setNextSpot(rowFinal*16, direction);
        }
    }
    else if(direction.compare("DOWN") == 0) 
    {
        while(colisions[rowFinal][colFinal] == 0) 
        {
            rowFinal++;
        } 
        rowFinal--;

        if(row == rowFinal) 
        { // if the position isn't modified it has to break
            block->destroyBlock();
        } 
        else 
        {// else it can move to the next spot
            block->setNextSpot(rowFinal*16, direction);
        }
    }
    else if(direction.compare("LEFT") == 0)
    {
        while(colisions[rowFinal][colFinal] == 0) 
        {
            colFinal--;
        } 
        colFinal++;

        if(col == colFinal) 
        { // if the position isn't modified it has to break
            block->destroyBlock();
        } 
        else 
        {// else it can move to the next spot
            block->setNextSpot(colFinal*16, direction);
        }

    }
    else if(direction.compare("RIGHT") == 0)
    {
        while(colisions[rowFinal][colFinal] == 0) 
        {
            colFinal++;
        } 
        colFinal--;
        
        if(col == colFinal) 
        { // if the position isn't modified it has to break
            block->destroyBlock();
        } 
        else 
        {// else it can move to the next spot
            block->setNextSpot(colFinal*16, direction);
        }
    }

    colisions[rowFinal][colFinal] = 1;
    //block->setPosition(sf::Vector2f(colFinal*16, rowFinal*16));
}

void Map::checkDirection(Enemy* e)
{
    int row = e->getPosition().y/16;
    int col = e->getPosition().x/16;

    if(colisions[row-1][col] != 0) // si arriba colisiona
    {
        e->setCanGo(1, false);
    }
    else
    {
        e->setCanGo(1, true);
    }

    if(colisions[row+1][col]) // si colisiona abajo
    {
        e->setCanGo(3, false);
    }
    else
    {
        e->setCanGo(3, true);
    }

    if(colisions[row][col+1]) // si colisiona derecha
    {
        e->setCanGo(2, false);
    }
    else
    {
        e->setCanGo(2, true);
    }
    if(colisions[row][col-1]) // si colisiona izquierda
    {
        e->setCanGo(4, false);
    }
    else
    {
        e->setCanGo(4, true);
    }
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
    

    for(unsigned i = 0; i < enemies.size(); i++) {
        enemies.at(i)->draw(window);
        // dest_blocks.at(i)->drawGizmo(window);
    }
    
}




