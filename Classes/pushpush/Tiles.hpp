#ifndef __PUSHPUSH_TILES_HPP__
#define __PUSHPUSH_TILES_HPP__

#include <vector>

#include "Util.hpp"

namespace pushpush {

class Tile {
  public:
    virtual ~Tile() { }
    virtual bool checkMovable() = 0;

};

class TileWall : public Tile {
  public:
    virtual ~TileWall() { }
    virtual bool checkMovable() {
        return false;
    }
};

class TileBackground : public Tile {
  public:
    virtual ~TileBackground() { }
    virtual bool checkMovable() {
        return false;
    }
};

class TileMovable : public Tile {
  public:
    virtual ~TileMovable() { }
    virtual bool checkMovable() {
        return true;
    }
};

};

#endif
