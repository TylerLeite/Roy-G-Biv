#include "map.h"

Map() : tiles(MAX_BOARD_WDT, MAX_BOARD_HGT, NULL, NULL)
{
    player = new Mob;
}
        
~Map(){
    for (int i = 0; i < mobs.size(); i++){
        delete mobs[i];
    }
    
    for (int y = 0; y < tiles.getHeight(); y++){
        for (int x = 0; x < tiles.getWidth(); x++){
            delete tiles.getAt(x, y);
        }
    }

    delete player;
}


int Map::update(){
    for (int y = 0; y < M_HG; y++){
        for (int x = 0; x < M_WD; x++){
            tiles.getAt(x, y)->update();
        }
    }
    
    for (int i = 0; i < mobs.size(); i++){
        mobs[i]->update();
    }
    
    player->update();
}

void Map::render(){
    for (int y = 0; y < M_HG; y++){
        for (int x = 0; x < M_WD; x++){
            tiles.getAt(x, y)->renderAt(x, y);
        }
    }
    
    for (int i = 0; i < mobs.size(); i++){
        mobs[i]->render();
    }
    
    player->render();
}


void Map::loadMap(const char* filen){
    std::ifstream file(filen);
    
    if (!file.is_open()){ //on error
        std::cerr << "ERROR: File \"" << filen << "\" not found!" << std::endl;
    } else {
        int tile = 3;
        for (int y = 0; y < tiles.getHeight(); y++){
            for (int x = 0; x < tiles.getWidth(); x++){
                file >> tile;
                file.ignore(1);
                
                tiles.getAt(x, y)->changeTo(tile);
                if (tile == RGB_TILE_START){ //8
                    player.jumpTo(x, y);
                }
            }
        }
        
        file.close();
        //std::cout << "Level loaded: " << filen << std::endl;
    }
}

int Map::checkStatus(){
    //win-condition is when there are only black/red tiles and  the player is on 
    // the end tile
    //lose-condition is when the player steps on a black tile
    Tile* curTile = getTile(player.mapX, player.mapY);
    if (curTile->curColor == BLACK){
        return -1; //lose
    } else {
        if (curTile->type == END_TILE){
            bool win = true;
            for (int y = 0; y < tiles.height(); y++){
                for (int x = 0; x < tiles.width(); x++){
                    curTile = tiles.getAt(x, y);
                    if ((curTile->type == END_TILE) 
                     || (curTile->type == START_TILE)){
                        continue;
                    } else if (curTile->curColor != RED 
                            && curTile->curColor != BLACK){
                        win = false;
                        break;
                    }
                }
            }
            
            if (win){
                return 1; //win
            }
        }
    }
    
    return 0; //no game over
}

bool Map::moveMob(Mob* mob=player, int direction){
    //TODO: get T_WD and T_HG as a function for resizing
    int x = mob->mapX;
    int y = mob->mapY;
    int vert = 0;
    int horz = 0;

    if (direction == NORTH){
        vert = -game->settings.getMapProperty("tile height");
        y--;
    } else if (direction == SOUTH){
        vert = game->settings.getMapProperty("tile height");
        y++; 
    } else if (direction == WEST){
        horz = -game->settings.getMapProperty("tile width");
        x--;
    } else if (direction == EAST){
        horz = game->settings.getMapProperty("tile width");
        x++;
    }

    bool walkable = false;
    if (tiles.inBounds(x, y)){
        if (tiles.getAt(x, y)->curColor != BLACK || mob->canFly){
            walkable = true;
        }
    }
    
    //only update they player's position / animation if he can move in the direction
    if (walkable){
        mob->setMapX(x);
        mob->setMapY(y);
        mob->setHorz(horz);
        mob->setVert(vert);
        mob->setMoving(true);
        getTile(x, y)->stepOn();
        return true;
    } else {
        return false;
    }
}
