#ifndef __PUSHPUSH_TILES_HPP__
#define __PUSHPUSH_TILES_HPP__

#include <vector>

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
    virtual bool checkMovable() {
        return false;
    }
};

class TileMovable : public Tile {
    virtual bool checkMovable() {
        return true;
    }
};

};

#endif
