#include "map.h"

Map::Map(){
    player.name = PLAYER_NAME;
    
    for (int x = 0; x < M_WD; x++){
        for (int y = 0; y < M_HG; y++){
            tiles[y][x] = new Tile(2);
        }
    }
}

Map::~Map(){
    //free tiles
    for (int x = 0; x < M_WD; x++){
        for (int y = 0; y < M_HG; y++){
            delete tiles[y][x];
        }
    }
}

bool Map::input(bool& paused){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == Settings::quit){
                        return false;
                    } else if (event.key.keysym.sym == Settings::up){
                        if (player.isMoving){
                            break;
                        } else {
                            movePlayer(UP);
                            break;
                        }
                    } else if (event.key.keysym.sym == Settings::pause){
                        paused = !paused;
                    }
                    
                    if (!paused){
                        if (event.key.keysym.sym == Settings::down){
                            if (player.isMoving){
                                break;
                            } else {
                                movePlayer(DOWN);
                                break;
                            }
                        } else if (event.key.keysym.sym == Settings::left){
                            if (player.isMoving){
                                break;
                            } else {
                                movePlayer(LEFT);
                                break;
                            }
                        } else if (event.key.keysym.sym == Settings::right){
                            if (player.isMoving){
                                break;
                            } else {
                                movePlayer(RIGHT);
                                break;
                            }
                        }
                    }
                    break;
                case SDL_QUIT:
                    return false; //Quit when the close button is pressed (above the window)
                    break;
                default: //Do nothing if there is no input
                    break;
            }
        } //Event loop stop
        
    return true;
}

int Map::checkStatus(){
  //win-condition is when there are only black/red tiles and  the player is on the end tile
  //lose-condition is when the player steps on a black tile
    Tile* curTile = getTile(player.mapX, player.mapY);
    if (curTile->curColor == BLACK){
        return -1;
    } else {
        if (curTile->type == END_TILE){
            bool win = true;
            for (int x = 0; x < M_WD; x++){
                for (int y = 0; y < M_HG; y++){
                    curTile = getTile(x, y);
                    if ((curTile-> type == END_TILE) || (curTile->type == START_TILE)){
                        continue;
                    } else if ((curTile->curColor != RED) && curTile->curColor != BLACK){
                        win = false;
                        break;
                    }
                }
            }
            
            if (win){
                return 1;
            }
        }
    }
    
    return 0;
}

void Map::update(){
    for (int y = 0; y < M_HG; y++){
        for (int x = 0; x < M_WD; x++){
            getTile(x, y)->update();
        }
    }
    
    for (int i = 0; i < mobs.size(); i++){
        mobs[i]->update();
    }
    
    player.update();
}

void Map::render(){
    for (int y = 0; y < M_HG; y++){
        for (int x = 0; x < M_WD; x++){
            getTile(x, y)->render(x, y);
        }
    }
    
    for (int i = 0; i < mobs.size(); i++){
        mobs[i]->render();
    }
    
    player.render();
}

bool Map::walkable(int x, int y){
    if ((x < 0) || (x >= M_WD) ||
        (y < 0) || (y >= M_HG)){
            return false;
    }
    
    if (getTile(x, y)->curColor == BLACK){
        return false;
    }
    
    return true;
}

bool Map::movePlayer(int direction){
    int x = player.mapX;
    int y = player.mapY;
    int vert = 0;
    int horz = 0;

    if (direction == UP){
        vert = -T_HG;
        y--;
    } else if (direction == DOWN){
        vert = T_HG;
        y++; 
    } else if (direction == LEFT){
        horz = -T_WD;
        x--;
    } else if (direction == RIGHT){
        horz = T_WD;
        x++;
    }
    
  //only update they player's position / animation if he can move in the direction
    if (walkable(x, y)){
        player.mapX = x;
        player.mapY = y;
        player.horz = horz;
        player.vert = vert;
        player.isMoving = true;
        getTile(x, y)->steppedOn = true;
        return true;
    } else {
        return false;
    }
}

void Map::tileFactory(int tile, Tile* proof){
    if (tile >= BLACK && tile <= VIOLET){
        proof->type = NORMAL_TILE;
        proof->curColor = tile;
    } else if (tile == START){
        proof->type = START_TILE;
        proof->curColor = 8;
    } else if (tile == END){
        proof->type = END_TILE;
        proof->curColor = 9;
    } else {
        //todo: figure something out for autotiles
    }
}

void Map::loadMap(const char* filen){
    
    ifstream file(filen);
    
    if (!file.is_open()){ //on error
        cout << "I AM ERROR: File \"" << filen << "\" not found!\n";
    } else {
        int tile = 3;
        unsigned tmpEnt;
        for (int y = 0; y < M_WD; y++){
            for (int x = 0; x < M_HG; x++){
                file >> tile;
                file.ignore(1);
                
                tileFactory(tile, getTile(x, y));
                if (tile == 8){
                    player.jumpTo(x, y);
                }
            }
        }
        
        file.close();
        cout << "Level loaded: " << filen << "\n";
    }
    
    /*
    for (int y = 0; y < M_HG; y++){
        for (int x = 0; x < M_WD; x++){
            cout << getTile(x, y)->curColor;
        }
        cout << "\n";
    }
    //*/
}

Tile* Map::getTile(int x, int y){
    return tiles[y][x];
}
