#ifndef __PUSHPUSH_LEVEL_HPP__
#define __PUSHPUSH_LEVEL_HPP__

#include "Util.hpp"

namespace pushpush {

class Tile {
  public:
    virtual bool checkMovable() = 0;
};

class TileWall : public Tile {
    virtual bool checkMovable() {
        return false;
    }
};

class TileBackground : public Tile {
};

class TileMovable : public Tile {
    virtual bool checkMovable() {
        return true;
    }
};

class Level {
  public:
    Level() {
    }
};

};

#endif
