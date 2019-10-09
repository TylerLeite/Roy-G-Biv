// Local dependencies
#include "defines.h"
#include "render.h"

void render::Init (SDL_Window* window, SDL_Screen* screen) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
  } else {
    // Create window
    window = SDL_CreateWindow(
      "SDL Tutorial",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
      cout << "Window could not be created! SDL_Error:" << SDL_GetError() << endl;
    } else {
      surface = SDL_GetWindowSurface(window);
      SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0x55, 0xBB, 0xFF));
      SDL_UpdateWindowSurface(window);

      SDL_Delay(2000);
    }
  }
}

void render::DrawTile (SDL_Screen* screen) {
  return;
}

void render::DrawMob (SDL_Screen* screen) {
  return;
}

void render::DrawMap (SDL_Screen* screen) {
  //
}
