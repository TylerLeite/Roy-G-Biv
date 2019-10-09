#include "game.h"

Game::Game(size_t width, size_t height) :
  _width(width), _height(height)
{
  const size_t length = width * height;
  _board = new Tile*[length];
  for (size_t i = 0; i < length; i++) {
    _board[i] = new Tile(Tile::AIR);
  }
}

Game::loadMap (const string& filen) {
  ifstream file;
  file.open(filen);
  char tile;

  const size_t length = _width * _height;
  for (size_t i = 0; i < length; i++) {
    file >> tile; // read one char at a time

    if (tile == '.') {
      _board[i]->TransformTo(Tile::AIR);
    } else if (tile == 'S') {
      _board[i]->TransformTo(Tile::START);
    } else if (tile == 'E') {
      _board[i]->TransformTo(Tile::END);
    } else {
      // tile - 48 is its number, + 1000 to avoid collisions with special tiles
      _board[i]->TransformTo(tile + 952);
    }
  }

  file.close();
}


// Ascii representation of the game
ostream &operator<< (ostream& os, const Game& game) {
  const size_t boardWidth = game.width();

  const Mob* mob = game.getMob(i);
  if (mob != nullptr) {
    os << mob;
  } else {
    const int boardSize = game.size();
    for (size_t i = 0; i < boardSize; ++i) {
      os << game.getTile(i);
    }
  }

  if (i == boardWidth) {
    os << endl;
  }

  return os;
}
