#include "Game.h"

Game::Game()
{
    window.create(sf::VideoMode(800, 720), "Pengo");
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(30);
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


    player = new Player(8,8);
    actualMap = new Map();


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
    player->update(elapsedTime);
}

void Game::render()
{
    window.clear();

    player->draw(window);
    actualMap->draw(window);
    window.display();
}