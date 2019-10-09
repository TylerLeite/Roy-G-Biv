#ifndef MOB_H
#define MOB_H

#include "defines.h"
#include "settings.h"

#include "renderSprite.h"

#include <string>
using std::string;

#include <fstream>
using std::ifstream;

#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout;
using std::cin;

class Mob{
    public:
        string name, animation;
        int direction, frame, animDelay,
            posX, posY, mapX, mapY,
            vert, horz;
        bool isMoving;
        
        
        Mob();
        
        void update();
        void render();
        
        void act();
        
        void jumpTo(int x, int y);
        void moveTo(int x, int y);
};

#endif
