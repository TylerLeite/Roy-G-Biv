// STL dependencies
#include <iostream>
#include <string>
using namespace std;

// External dependencies
#include <SDL2/SDL.h>

// Local dependencies
#include "defines.h"

int main (int argc, char** argv) {
  // Initialize SDL
  SDL_Window* window = nullptr;
  SDL_Surface* surface = nullptr;
  render::init(window, surface);

  // Initialize game
  Game* game = new Game(BOARD_WIDTH, BOARD_HEIGHT);
  string mapname = "1.map";
  game->loadMap(mapname);

  // Cleanup
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
