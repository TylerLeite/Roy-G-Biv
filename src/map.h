#ifndef MAP_H
#define MAP_H

#include <vector>

#include "grid2d.h"
#include "mob.h"
#include "tile.h"

class Map {
    public:
        Map();
        ~Map();

        void update();
        void render();

        void loadMap(const char* filen);
        int checkStatus(); //gameover, win / lose, quit, unsolved, etc

        bool moveMob(Mob* mob=player, int direction);

    protected:
        Grid2d<Tile*> tiles;
        vector<Mob*> mobs
        Mob* player; //note: not in vector of mobs
};

#endif
