#ifndef MAP_H
#define MAP_H

#include "defines.h"
#include "settings.h"

#include "mob.h"
#include "tile.h"

#include <cstdlib>

#include <vector>
using std::vector;

#include <SDL2/SDL.h"
#include <SDL2/SDL_opengl.h"

class Map {
    public:
        Tile* tiles[M_WD][M_HG];
        vector<Mob*> mobs;
        
        Mob player;
        
        Map();
        ~Map();
        
        bool input(bool& paused); //poll for input and act based on it
        
        int checkStatus(); //check whether the game is over
        
        void update();
        void render();
        
        bool walkable(int x, int y); //return true if (x, y) is in the map and not null
        bool movePlayer(int direction); //attempt to move the player, return false if unable
        
        void tileFactory(int tile, Tile* proof); //transform an existing tile to be of type "tile"
        void loadMap(const char* filen); //load a map from /maps/
        
        Tile* getTile(int x, int y);
};

#endif
