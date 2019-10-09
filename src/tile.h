#ifndef TILE_H
#define TILE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "render.h"

//tiles are 16 bit numbers, first 5 don't encode anything, the next 4 bits are
// the primary type, next 4 after that are the secondary type, and last 3  are
// are the color

// 0000 - normal tile / no secondary
// 0001 - autotile ticking once per 3 steps
// 0010 - autotile ticking once per 5 steps
// 0011 - 
// 0100 - slippery tile
// 0101 - inverse tile
// 0110 - start tile
// 0111 - end tile
// 1000 - mobkill tile
// 1001 - portal tile
// 1010 - reverse inverse tile
// 1011 - switcher tile
// 1100 - super slip tile
// 1101 - one-way portal tile, send
// 1110 - one-way portal tile, recieve
// 1111 - infect tile

// 0000 - black
// 0001 - red
// 0010 - orange
// 0011 - yellow
// 0100 - green
// 0101 - blue
// 0110 - indigo
// 0111 - violet

class Map;

class Tile {
    public:
        int type;

        int startingColor;
        int curColor;
        bool steppedOn;

        Map* map;
        
        Tile(Map* map);
        Tile(Map* map, int type, int startingColor);

        //virtual ~Tile();
        
        virtual void tickDown();
        virtual void onStep();
        virtual void update();
        virtual void render(int x, int y);
};

class AutoTile : public Tile {
    public:
        int fuseLength, curFuse;

        AutoTile(int startingColor, int fuseLength);

        void tickDown();
        void onStep();        
        void update();
        void render(int x, int y);
};

class SlipperyTile : public Tile {
    public:
        SlipperyTile(int startingColor);

        void onStep();
        void update();
        void render(int x, int y);
};

class InverseTile : public Tile {
    public:
        InverseTile(int startingColor);

        void onStep();
        void update();
        void render(int x, int y);
};

class MobKillTile : public Tile {
        MobKillTile(int startingColor);

        void onStep();
        void update();
        void render(int x, int y);
};

#endif
