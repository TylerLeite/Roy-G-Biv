#include "tile.h"

Tile::Tile(){
    type = NORMAL_TILE;

    startingColor = VIOLET;
    curColor  = VIOLET;
    steppedOn = false;
    
    fuseLength  = -1;
    curFuse = -1;
}

Tile::Tile(int startingColor){
    type = NORMAL_TILE;
    
    this->startingColor = startingColor;
    curColor = startingColor;
}

Tile::Tile(int startingColor, int fuseLength){
    type = AUTO_TILE;
    
    this->startingColor = startingColor;
    curColor = startingColor;
    
    this->fuseLength = fuseLength;
    curFuse = fuseLength;
}

void Tile::tickDown(){
    if (curColor > 0){
        curColor--;
    }
}

void Tile::update(){
    switch (type){
        case NORMAL_TILE:
            if (steppedOn){
                tickDown();
                steppedOn = false;
            }
            break;
        case AUTO_TILE:
            if (steppedOn){
                tickDown();
                steppedOn = false;
            } else {
                if (curFuse >= 0){
                    curFuse -= 1;
                } else {
                    curFuse = fuseLength;
                    tickDown();
                }
            }
            
            if (curColor == BLACK){
                type = NORMAL_TILE;
            }
            break;
        default:
            break;
    }
}

void Tile::render(int x, int y){
    int sprite;
    if (type == START_TILE){
        sprite = 8;
    } else if (type == END_TILE){
        sprite = 9;
    } else {
        sprite = curColor;
    }
    
    stringstream spriteFile;
    spriteFile << "graphics/tilesets/" << Settings::tileset << "/tiles/" << sprite << ".png";
    string filen = spriteFile.str();
    
    renderSpriteAt(filen, x, y);
    
    if (type == AUTO_TILE){
        stringstream textFile;
        textFile << "graphics/tilesets" << Settings::tileset << "/numbers/" << curFuse << ".png";
        filen = textFile.str();
        renderSprite(filen, N_WD, N_HG, x*T_WD + N_WD, y*T_HG + 2*N_HG);
    }
}
