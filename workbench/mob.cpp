#include "mob.h"

Mob::Mob() :
    name("undef"), animation("stopped"),
    direction(DOWN), frame(0), animDelay(25),
    posX(0), posY(0), mapX(0), mapY(0),
    vert(0), horz(0),
    isMoving(false)
{}

void Mob::update(){
    if (animDelay > 0){
        animDelay--;
    } else {
        animDelay = Settings::fps/2;
        if (frame == 0){
            frame = 1;
        } else if (frame == 1){
            frame = 0;
        }
    }
    
    if (isMoving){
        if (horz != 0){
            if (horz > 0){
                direction = RIGHT;
                horz--;
                posX++;
            } else if (horz < 0){
                direction = LEFT;
                horz++;
                posX--;
            }
        } else if (vert != 0){
            if (vert > 0){
                direction = DOWN;
                vert--;
                posY++;
            } else if (vert < 0){
                direction = UP;
                vert++;
                posY--;
            }
        }
        
        if ((horz == 0) && (vert == 0)){
            isMoving = false;
        }
    }
}

void Mob::render(){
    string animation;
    if (isMoving){
        animation = "walking";
    } else {
        animation = "stopped";
    }
    
    if (direction == UP){
        animation += "_up_";
    } else if (direction == DOWN){
        animation += "_down_";
    } else if (direction == LEFT){
        animation += "_left_";
    } else if (direction == RIGHT){
        animation += "_right_";
    }
    
    stringstream spriteFile;
    if (name == PLAYER_NAME){
        spriteFile << "graphics/skins/" << Settings::skin << "/" << animation << frame << ".png";
    } else {
        spriteFile << "graphics/tilesets/" << Settings::tileset <<"/mobs/" << name << "/"<< animation << frame << ".png";
    }
    string filen = spriteFile.str();
    
    renderSprite(filen, T_WD, T_HG, posX, posY);
}

void Mob::jumpTo(int x, int y){
    mapX = x;
    mapY = y;
    
    posX = x*T_WD;
    posY = y*T_HG;
    
    animation = "stopped";
    frame = 0;
    direction = DOWN;
    
    isMoving = false;
    horz = 0;
    vert = 0;
    
}
