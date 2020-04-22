#include "Game.h"

Game::Game()
{
    window.create(sf::VideoMode(800, 720), "Pengo");
    window.setVerticalSyncEnabled(true);
    // window.setFramerateLimit(30);
    // view.zoom(0.23f);
    view.zoom(0.26f);

}


Game::~Game()
{
    // destructor
}


void Game::start() 
{
    declarations();

    while(window.isOpen()) {
        events();

        if(updatesPS.getElapsedTime().asMilliseconds() - timesUpdate.asMilliseconds() > updateTimePS) {
            updateGame(gameUpdate.restart().asMilliseconds());
            timesUpdate = updatesPS.getElapsedTime();
        }

        render();
    }
}


void Game::declarations()
{
    timesUpdate = updatesPS.getElapsedTime();
    
    // first the map
    actualMap = new Map();
    actualMap->loadLevel(1);


    player = new Player(actualMap->getPlayerPosition().x, actualMap->getPlayerPosition().y);

    // std::cout << actualMap->getViewPosition().x << ", " << actualMap->getViewPosition().y << std::endl;
    view.setCenter(actualMap->getViewPosition().x + 6, actualMap->getViewPosition().y - 14);

}


void Game::events()
{
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
        
        if(event.key.code == sf::Keyboard::Escape) {
            // Show pause menu, but for now, just close the game
            window.close();
        }
    }
}


void Game::updateGame(float elapsedTime)
{



    if(player->isDead()) // If the player dies
    {
        if(actualMap->getPlayerLifes() > 0) // just ressets the player
        {
            if(player->isXkeyPressed()) // in case you press the X key to die and restart
            {
                int lvl = actualMap->getLvlLoaded();
                actualMap = new Map();
                actualMap->loadLevel(lvl);
                player = new Player(actualMap->getPlayerPosition().x, actualMap->getPlayerPosition().y);    
            }
            else // if the player still has lives
            {
                actualMap->subtractLife();
                player = new Player(actualMap->getPlayerPosition().x, actualMap->getPlayerPosition().y);
            }
            
        }
        else // if the player has no more lives
        {
            int lvl = actualMap->getLvlLoaded();
            actualMap = new Map();
            actualMap->loadLevel(lvl);
            player = new Player(actualMap->getPlayerPosition().x, actualMap->getPlayerPosition().y);    
        }   
    }
    else if(actualMap->getTotalEnemies() <= 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::N)) // check the total enemies
    {
        int lvl = actualMap->getLvlLoaded() + 1;
        if(lvl > 2)
        {
            lvl = 1;
        }
        actualMap = new Map();
        actualMap->loadLevel(lvl);
        player = new Player(actualMap->getPlayerPosition().x, actualMap->getPlayerPosition().y);
    }
    else
    {
        moveView();
        actualMap->update(player);
        player->update(elapsedTime);
    }
}

void Game::moveView()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(player->getPosition().y >= 9*16 && player->getPosition().y <= 13*16)
        {
            if(view.getCenter().y < 9*16)
            {
            view.move(sf::Vector2f(0, 2));
            }
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {

        if(player->getPosition().y <= 9*16)
        {
            if(view.getCenter().y > actualMap->getViewPosition().y)
            {
                view.move(sf::Vector2f(0, -2));
            }
        }

    }
}

void Game::render()
{
    window.clear();
    window.setView(view);
    actualMap->draw(window);
    player->draw(window);
    window.display();
}