#ifndef RENDER_SPRITE_H
#define RENDER_SPRITE_H

#include "defines.h"

#include <string>
using std::string;

#include <iostream>
using std::cout;

#include <map>
using std::map;

using std::pair;

#include <SDL2/SDL.h"
#include <SDL2/SDL_opengl.h"
#include <SDL2/SDL_image.h"

static map<string, unsigned> textures;

unsigned loadTexture(const string& filen);
void renderSprite(const string& filen, const unsigned& width, const unsigned& height, const int& posX, const int& posY);
void renderSpriteAt(const string& filen, const int& mapX, const int& mapY);

#endif
