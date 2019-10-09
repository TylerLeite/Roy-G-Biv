#ifndef RENDER_H
#define RENDER_H

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

static map<std::string, int> textures;

unsigned loadTexture(const std::string& filen);

void renderAt(const std::string& filen, int width, int height, int pos_x, int pos_y);

void renderOn(const std::string& filen, int map_x,  int map_y);


#endif
