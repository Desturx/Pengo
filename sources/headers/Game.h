#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Map.h"


#define updateTimePS 1000/30

class Game {
    public:
        Game();
        virtual ~Game();
        void start();
        void events();
        void declarations();
        void updateGame(float elapsedTime);
        void render();
        void moveView();
    private:

        sf::RenderWindow window;
        

        // Clocks
        sf::Clock updatesPS;
        sf::Clock gameUpdate;
        sf::Time timesUpdate;

        // Event
        sf::Event event;

        // View
        sf::View view;

        // Game objects
        Player* player;
        Map* actualMap;




};