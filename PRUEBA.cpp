#include <SFML/Graphics.hpp>

sf::RenderWindow mywindow(sf::VideoMode(800,600,32),"title");
sf::Event ev;

int tilesize = 50;

class character
{
public:
        character()
        {
                x = 0;
                y = 0;
                
                // in this case, every loop, it will walk 2 pixels. 
        //if u put 50 as movespeed, it will walk 1 pixel each loop
                movespeed = 100.0 / tilesize; 

                for(int i = 0; i < 4; ++i) //initialize the all move booleans to false
                        move[i] = false;

                walking = false;
                myrect.setSize(sf::Vector2f(50,50)); //size 50 by 50, same as every tile
        }

        void keymove(); //keypress detection
        void moving(); //moving if "walking" boolean is true

        float x;
        float y;
        float movespeed; //sets the movespeed

        enum MOVE {UP,DOWN,LEFT,RIGHT}; //enums instead of remember numbers
        bool move[4]; //deciding if u move up/down/left/right
        bool walking;
        int nextspot; //the next tilespot of the map

        sf::RectangleShape myrect;
};

void character::keymove()
{
        /*keymove() and moving() functions are working together*/
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
                if(walking == false) 
                {
                        /*if you click up, the the nextspot will of course be 50
                        pixels above yourself, so thats why nextspot = y - tilsize*/
                        nextspot = y - tilesize; 
                        /*this is gonna make sure you cant have move[UP] and move[LEFT]
                        true on the same time so u wont walk 45 degrees*/
                        move[UP] = true;
                        walking = true; 
                        
                }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
                if(walking == false)
                {
                        nextspot = y + tilesize;
                        move[DOWN] = true;
                        walking = true;
                }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
                if(walking == false)
                {
                        nextspot = x - tilesize;
                        move[LEFT] = true;
                        walking = true;
                }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
                if(walking == false)
                {
                        nextspot = x + tilesize;
                        move[RIGHT] = true;
                        walking = true;
                }
        }
}
void character::moving()
{
        if(walking == true)
        {
                if(move[UP] == true)
                {
                        y -= movespeed;

                        /* i do <= and not just == because maybe your movespeed has a
                        decimalpoint and then it wont become the same number as nextspot*/
                        if(y <= nextspot)
                        {
                                y = nextspot; 
                                walking = false;
                                move[UP] = false;
                        }
                }

                if(move[DOWN] == true)
                {
                        y += movespeed;
                        if(y >= nextspot)
                        {
                                y = nextspot;
                                walking = false;
                                move[DOWN] = false;
                        }
                }
                if(move[LEFT] == true)
                {
                        x -= movespeed;
                        if(x <= nextspot)
                        {
                                x = nextspot;
                                walking = false;
                                move[LEFT] = false;
                        }
                }
                if(move[RIGHT] == true)
                {
                        x += movespeed;
                        if(x >= nextspot)
                        {
                                x = nextspot;
                                walking = false;
                                move[RIGHT] = false;
                        }
                }
        }
}
int main()
{
        mywindow.setVerticalSyncEnabled(true); // 60 fps
        character pacman; // a squared pacman
    pacman.myrect.setFillColor(sf::Color(255,255,0));
        while(mywindow.isOpen())
        {
                while(mywindow.pollEvent(ev))
                {
                        if(ev.type == sf::Event::Closed) mywindow.close();
                }

                pacman.keymove();
                pacman.moving();
                pacman.myrect.setPosition(pacman.x,pacman.y);

                mywindow.clear(sf::Color(0,200,0));
                mywindow.draw(pacman.myrect);

                mywindow.display();
        }
}