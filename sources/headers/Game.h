#include <SFML/Graphics.hpp>
#include <iostream>


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
    private:

        sf::RenderWindow window;

        // Clocks
        sf::Clock updatesPS;
        sf::Clock gameUpdate;
        sf::Time timesUpdate;

        // Event
        sf::Event event;

        // Game objects



};