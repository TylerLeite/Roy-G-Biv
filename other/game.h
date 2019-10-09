#ifndef GAME_H
#define GAME_H

// STL dependencies
#include <string>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

// Local dependencies
#include "defines.h"
#include "tile.h"
#include "mob.h"

class Game {
  Tile** _board;
  map<int, Mob*> _mobs;
  size_t _width, _height

public:
  Game(size_t width, size_t height);
  ~Game();

  // Game logic
  void input();
  void update();
  void render();

  // Mutators
  void loadMap(const string& filen);
  Tile* setTile(Tile* tile, size_t i);
  Tile* setTile(Tile* tile, size_t x, size_t y);
  Mob* addMob(Mob* mob, size_t i);
  Mob* addMob(Mob* mob, size_t x, size_t y);
  Mob* removeMob(size_t i);
  Mob* removeMob(size_t x, size_t y);
  Mob* moveMob(size_t start, size_t end);
  Mob* moveMob(size_t xStart, size_t yStart, size_t xEnd, size_t yEnd);

  // Getters
  Tile* getTile(size_t i);
  Tile* getTile(size_t x, size_t y);
  Mob* getMob(size_t i);
  Mob* getMob(size_t x, size_t y);
  size_t size();
  size_t width();
  size_t height();

  // Friends
  friend ostream& operator<<;
};

ostream &operator<< (ostream& os, const Game& game);

#endif
