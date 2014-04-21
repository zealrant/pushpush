#ifndef __PUSHPUSH_LEVEL_HPP__
#define __PUSHPUSH_LEVEL_HPP__

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

class Level {
    Size size;
    Point posStart;
    std::vector<Point*> houses;
    std::vector<Point*> balls;
    std::vector<Tile*> tiles;

  public:
    Level(Size s, Point p, std::vector<Point*> h,
          std::vector<Point*> b, std::vector<Tile*> t)
            : size(s), posStart(p), houses(h), balls(b), tiles(t) {
    }

    virtual ~Level() {
        Deletor<Tile> deletorTile;
        for_each(tiles.begin(), tiles.end(), deletorTile);
        for_each(houses.begin(), houses.end(), deletorPoint);
        for_each(balls.begin(), balls.end(), deletorPoint);
    }

    Tile* getTileAtPos(int x, int y) {
        return tiles[y * size.width + y];
    }
};

};

#endif
