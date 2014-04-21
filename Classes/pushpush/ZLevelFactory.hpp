#ifndef __PUSHPUSH_ZLEVEL_FACTORY_HPP__
#define __PUSHPUSH_ZLEVEL_FACTORY_HPP__

#include "LevelFactory.hpp"

USING_NS_CC;

namespace pushpush {

class ZLevelFactory : public LevelFactory {
    CCLayer* layer;
    static const int TILE_SIZE;
    static const int TILE_WALL;
    static const int TILE_MOVABLE;
    static const int TILE_BACKGROUND;
    static const char* stageFileNames[];

  private:
    inline int offsetForKey(CCDictionary* const dic, const char* key) const {
        return dic->valueForKey(key)->intValue() / TILE_SIZE;
    }

    void buildPoints(CCTMXTiledMap* const map, const char* layerName,
                     LevelBuilder* builder,
                     LevelBuilder* (LevelBuilder::*func)(int, int)) {
        CCTMXObjectGroup* objGroup = map->objectGroupNamed(layerName);
        CCArray* arr = objGroup->getObjects();
        CCObject* obj;
        int x, y;
        CCARRAY_FOREACH(arr, obj) {
            x = offsetForKey((CCDictionary*)obj, "x");
            y = offsetForKey((CCDictionary*)obj, "y");
            (builder->*func)(x, y);
        }
        return;
    }

  public:
    ZLevelFactory(CCLayer* l) : layer(l) { }

    virtual Level* createLevel(int stage) {
        CCTMXTiledMap* map = CCTMXTiledMap::create(stageFileNames[stage]);
        layer->addChild(map, 0, 100);

        LevelBuilder builder;
        CCSize sz = map->getMapSize();
        builder.setSize(sz.width, sz.height);
        buildPoints(map, "SpawnPoint", &builder, &LevelBuilder::setHeroPos);
        buildPoints(map, "Balls", &builder, &LevelBuilder::addBall);
        buildPoints(map, "Houses", &builder, &LevelBuilder::addHouse);

        CCTMXLayer* walls = map->layerNamed("WallLayer");
        builder.setTiles(walls->getTiles(), [](int tileValue) {
                Tile* t;
                if(tileValue == TILE_BACKGROUND) {
                    t = new TileBackground();
                } else if(tileValue == TILE_WALL) {
                    t = new TileWall();
                } else if(tileValue == TILE_MOVABLE) {
                    t = new TileMovable();
                }
                return t;
            });
        Level *level = builder.build();
        return level;
    }
};

const int ZLevelFactory::TILE_SIZE = 33;
const int ZLevelFactory::TILE_BACKGROUND = 0;
const int ZLevelFactory::TILE_WALL = 49;
const int ZLevelFactory::TILE_MOVABLE = 50;
const char* ZLevelFactory::stageFileNames[] = {"stage1.tmx", "stage2.tmx"};

};

#endif
