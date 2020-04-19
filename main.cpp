#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "Game.h"

int main() {

  srand (time(NULL));
  
  Game newGame;
  newGame.start();

  return EXIT_SUCCESS;
}