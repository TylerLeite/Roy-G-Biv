#include "game.h"

/** TILE **/
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
            //todo: fix this so that it changes color when stepped on
            if (curFuse > 0){
                curFuse -= 1;
            } else {
                curFuse = fuseLength;
                tickDown();
            }
            break;
        default:
            break;
    }
}


void Tile::render(){
    stringstream waffen;
    waffen << "graphics/" << gameSettings::tileset << "/" << curLvl << ".map";
    string filen = waffen.str();
    map.loadMap(filen.c_str());
    
    loadSprite();
}

void Tile::renderAscii(){
    switch (type){
        case NORMAL_TILE:
            switch (curColor){
                case BLACK:
                    cout << color_BLACK  << CHAR_NORMAL_TILE << color_CLEAR;
                    break;
                case RED:
                    cout << color_RED    << CHAR_NORMAL_TILE << color_CLEAR;
                    break;
                case ORANGE:
                    cout << color_ORANGE << CHAR_NORMAL_TILE << color_CLEAR;
                    break;
                case YELLOW:
                    cout << color_YELLOW << CHAR_NORMAL_TILE << color_CLEAR;
                    break;
                case GREEN:
                    cout << color_GREEN  << CHAR_NORMAL_TILE << color_CLEAR;
                    break;
                case BLUE:
                    cout << color_BLUE   << CHAR_NORMAL_TILE << color_CLEAR;
                    break;
                case INDIGO:
                    cout << color_INDIGO << CHAR_NORMAL_TILE << color_CLEAR;
                    break;
                case VIOLET:
                    cout << color_VIOLET << CHAR_NORMAL_TILE << color_CLEAR;
                    break;
                default:
                    break;
            }
            break;
        case AUTO_TILE:
            switch (curColor){
                case BLACK:
                    cout << color_BLACK  << curFuse << color_CLEAR;
                    break;
                case RED:
                    cout << color_RED    << curFuse << color_CLEAR;
                    break;
                case ORANGE:
                    cout << color_ORANGE << curFuse << color_CLEAR;
                    break;
                case YELLOW:
                    cout << color_YELLOW << curFuse << color_CLEAR;
                    break;
                case GREEN:
                    cout << color_GREEN  << curFuse << color_CLEAR;
                    break;
                case BLUE:
                    cout << color_BLUE   << curFuse << color_CLEAR;
                    break;
                case INDIGO:
                    cout << color_INDIGO << curFuse << color_CLEAR;
                    break;
                case VIOLET:
                    cout << color_VIOLET << curFuse << color_CLEAR;
                    break;
                default:
                    break;
            }
            break;
        case END_TILE:
            cout << CHAR_END_TILE;
            break;
        case START_TILE:
            cout << CHAR_START_TILE;
            break;
        default:
            break;
    }
}

/** MAP **/
Map::Map(){
    quit = false;

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

bool Map::input(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){ //Event loop start
            switch (event.type){
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym){
                        case SDLK_ESCAPE: //Quit when escape is pressed
                            quit = true;
                            break;
                        default: //Do nothing if no key is pressed
                            break;
					}
				case SDL_QUIT:
					quit = true; //Quit when the close button is pressed (above the window)
					break;
                default: //Do nothing if there is no input
                    break;
			}
        } //Event loop stop
}

int Map::checkStatus(){
    if (quit){
        return -2;
    }

    Tile* curTile = getTile(playerX, playerY);
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
    for (int x = 0; x < M_WD; x++){
        for (int y = 0; y < M_HG; y++){
            getTile(x, y)->update();
        }
    }
    
    /*
    for (int i = 0; i < mobs.size(); i++){
        mobs[i].update();
    }
    //*/
}

void Map::render(){
    for (int x = 0; x < M_WD; x++){
        for (int y = 0; y < M_HG; y++){
            if ((x == playerX) && (y == playerY)){
                cout << CHAR_PLAYER;
            } else {
                getTile(x, y)->render();
            }
        }
        
        cout << '\n';
    }
    
    /*
    for (int i = 0; i < mobs.size(); i++){
        mobs[i].render();
    }
    //*/
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
    int x = playerX;
    int y = playerY;

    if (direction == UP){
        x--;
    } else if (direction == DOWN){
        x++; 
    } else if (direction == LEFT){
        y--;
    } else if (direction == RIGHT){
        y++;
    }
    
    if (walkable(x, y)){
        playerX = x;
        playerY = y;
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
    } else if (tile == 8){
        proof->type = START_TILE;
        proof->curColor = -1;
    } else if (tile == 9){
        proof->type = END_TILE;
        proof->curColor = -1;
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
        for (int x = 0; x < M_WD; x++){
            for (int y = 0; y < M_HG; y++){
                file >> tile;
                file.ignore(1);
                
                tileFactory(tile, getTile(x, y));
                if (tile == 8){
                    playerX = x;
                    playerY = y;
                }
            }
        }
        
        file.close();
        cout << "Level loaded: " << filen << "\n";
    }
    
    render();
}

Tile* Map::getTile(int x, int y){
    return tiles[y][x];
}

/** GAME **/
Game::Game() :
    curLvl(1)
{}

void Game::startMenu(){
    cout << "Welcome to Roy G Biv! " ;
    
    while (true){
        int command;
        char c;
        cout << "What do you wanna do?\n" 
             << "\t1. Help\n" 
             << "\t2. Game\n"
             << "\t3. Options\n" 
             << "\t4. Exit\n"
             << "Your choice: ";
         cin >> command;
         
         switch (command){
            case 1:
                // Print help text (how to play)
                cout << "The goal of the game is to get all tiles to be" << color_RED << " Red. " << color_CLEAR << "You do this by"
                     << "walking. It's just that easy. Stepping on a tile will adjust a tile's"
                     << "color in the following order:" << color_VIOLET << " Violet " << color_CLEAR << "->" << color_INDIGO << " Indigo " << color_CLEAR << "->" << color_BLUE << " Blue " << color_CLEAR << "->" << color_GREEN << " Green " << color_CLEAR << "->"
                     << color_YELLOW << "Yellow " << color_CLEAR << "->" << color_ORANGE << " Orange " << color_CLEAR << "->" << color_RED << " Red. " << color_CLEAR << "If you step on a Red tile, it's game-over."
                     << "The tile will disappear and you will fall into oblivion. Then you"
                     << "will die. Alone. You control your character (Roy himself) with " << CTRL_UP << ", " << CTRL_DOWN << ","
                     << CTRL_LEFT << ", and " << CTRL_RIGHT << " to move Up, Down, Left, and Right respectively. Once all the"
                     << "tiles are" << color_RED << " Red" << color_CLEAR << ", you must walk to the exit (hint: it looks a bit like"
                     << "this -> " << CHAR_END_TILE << ") (other hint: for those slightly dull, this means that you\n"
                     << "don't JUST need all the tiles to be red, you need to end up next to"
                     << "the exit) (other other hint: Press any key to return to the menu).";
                 cin >> c;
                break;
            case 2:
                // Start the main game
                startGame();
                break;
            case 3:
                //Todo: add options
                cout << "There are no options, press any key to get out: \n";
                cin >> c;
                break;
            case 4:
                //Quit the application
                return;
            default:
                break;
         }
     }
}

void Game::rollCredits(){
    return;
}


void Game::startGame(){
    bool quit = false;
    
    map.loadMap("map_1.map");
    while (!quit){
        if (map.input()){
            map.update();
        
            int status = map.checkStatus();
            if (status != 0){
                if (status == 1){
                    curLvl++;
                    cout << "You have completed the level, press the any key to start the next one.\n";
                    //wait for a response
                    char c;
                    cin >> c;
                } else if (status == -1){
                    cout << "You have died\n";
                } else if(status == -2){
                    return;
                }
                
                stringstream waffen;
                waffen << "maps/map_" << curLvl << ".map";
                string filen = waffen.str();
                map.loadMap(filen.c_str());
            } else {
                map.render(); 
            }
        }
    }
}


/*
The goal of the game is to get all tiles to be Red. You do this by
walking. It's just that easy. Stepping on a tile will adjust a tile's
color in the following order: Violet -> Indigo -> Blue -> Green ->
Yellow -> Orange -> Red. If you step on a red tile, it's game-over.
The tile will disappear and you will fall into oblivion. Then you
will die. Alone. You control your character (Roy himself) with W, A,
S, and D to move Up, Down, Left, and Right respectively. Once all the
tiles are Red, you must walk to the exit (hint: it looks a bit like
this -> E) (other hint: for those slightly dull, this means that you
don't JUST need all the tiles to be red, you need to end up next to
the exit) (other other hint: Press any key to return to the menu).
*/
