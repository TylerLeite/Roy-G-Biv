#ifndef __GAME_H__
#define __GAME_H__

#ifndef nullptr
    #define nullptr NULL
#endif

#define M_WD 8
#define M_HG 8

#define FINAL_LEVEL 2

#define CHAR_NORMAL_TILE '#'
#define CHAR_PLAYER '@'
#define CHAR_END_TILE 'E'
#define CHAR_START_TILE 'S'

#define CTRL_UP 'w'
#define CTRL_DOWN 's'
#define CTRL_LEFT 'a'
#define CTRL_RIGHT 'd'
#define CTRL_QUIT 'q'

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define NORMAL_TILE 0
#define AUTO_TILE 1
#define END_TILE 2
#define START_TILE 3

#define color_CLEAR "\033[0m"

#define BLACK 0
#define color_BLACK "\033[0;30m"

#define RED 1
#define color_RED "\033[0;31m"

#define ORANGE 2
#define color_ORANGE "\033[0;33m"

#define YELLOW 3
#define color_YELLOW "\033[1;33m"

#define GREEN 4
#define color_GREEN "\033[0;32m"

#define BLUE 5
#define color_BLUE "\033[0;36m"

#define INDIGO 6
#define color_INDIGO "\033[0;34m"

#define VIOLET 7
#define color_VIOLET "\033[0;35m"

#include "defines.h"

#include <string>
using std::string;

#include <fstream>
using std::ifstream;

#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout;
using std::cin;

class Tile {
    public:
        int type;

        int startingColor;
        int curColor;
        bool steppedOn;
        
        int fuseLength;
        int curFuse;
        
        Tile();
        Tile(int startingColor);
        Tile(int startingColor, int fuseLength);
        
        void update();
        void render();
        
        void tickDown();
};

class Map {
    public:
        Tile* tiles[M_WD][M_HG];
        //vector<Mob*> mobs;
        
        int playerX, playerY;
        bool quit;
        
        Map();
        ~Map();
        
        bool input();
        
        int checkStatus();
        
        void update();
        void render();
        
        bool walkable(int x, int y); //return if (x, y) is in the map and not null
        bool movePlayer(int direction); //attempt to move the player, return false if unable
        
        void tileFactory(int tile, Tile* proof);
        void loadMap(const char* filen);
        
        Tile* getTile(int x, int y);
};

class Game {
    public:
        int curLvl;
        Map map;
        
        int width;
		int height;
		unsigned fps;
        
        Game(int width, int height, int fps);
        
        void startMenu();
        void rollCredits();
        void startGame();
};

int main(int argc, char** argv){
    Game game;
    game.startMenu();
    
    return 0;
}

#endif //__GAME_H__
