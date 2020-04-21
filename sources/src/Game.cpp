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
    actualMap->loadLevel();


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



    if(player->isDead())
    {
        if(actualMap->getPlayerLifes() > 0)
        {
            if(player->isXkeyPressed())
            {
                actualMap = new Map();
                actualMap->loadLevel();
                player = new Player(actualMap->getPlayerPosition().x, actualMap->getPlayerPosition().y);    
            }
            else
            {
                actualMap->subtractLife();
                player = new Player(actualMap->getPlayerPosition().x, actualMap->getPlayerPosition().y);
            }
            
        }
        else
        {
        
            actualMap = new Map();
            actualMap->loadLevel();
            player = new Player(actualMap->getPlayerPosition().x, actualMap->getPlayerPosition().y);    

            

        }
        
    }
    else
    {
        actualMap->update(player);
        player->update(elapsedTime);
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