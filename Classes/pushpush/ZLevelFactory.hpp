#ifndef __PUSHPUSH_ZLEVEL_FACTORY_HPP__
#define __PUSHPUSH_ZLEVEL_FACTORY_HPP__

#include "LevelFactory.hpp"
#include "ZStory.hpp"

USING_NS_CC;

namespace pushpush {

class ZLevelBuilder : public LevelBuilder {
    ZObjectFactory* objFactory;

  public:
    ZLevelBuilder(ZObjectFactory* objF) : objFactory(objF) {
    }

    virtual LevelBuilder* setHeroPos(int x, int y) {
        Hero* h = objFactory->createHero(x, y);
        return LevelBuilder::setHero(h);
    }

    virtual LevelBuilder* addBall(int x, int y) {
        Ball* ball = objFactory->createBall(x, y);
        return LevelBuilder::addBall(ball);
    }

    virtual LevelBuilder* addHouse(int x, int y) {
        House* h = objFactory->createHouse(x, y);
        return LevelBuilder::addHouse(h);
    }
};

class ZLevelFactory : public LevelFactory {
    Layer* layer;
    StoryFactory* storyFactory;
    std::function<void()> levelDoneCallback;
    int initialX, initialY;
    static const int TILE_SIZE = 33;
    static const int TILE_WALL = 49;
    static const int TILE_MOVABLE = 50;
    static const int TILE_BACKGROUND = 0;
    static const char* stageFileNames[];

  private:
    void setInitialPoint(int x, int y) {
        initialX = x;
        initialY = y;
    }

    void buildPoints(ZLevelBuilder* builder,
                     LevelBuilder* (ZLevelBuilder::*func)(int, int),
                     TMXTiledMap* const map, const char* layerName) {
        TMXObjectGroup* objGroup = map->getObjectGroup(layerName);
        const ValueVector arr = objGroup->getObjects();
        // int x, y;

        for (Value v : arr) {
            ValueMap m = v.asValueMap();
            int x = m["x"].asInt() / TILE_SIZE;
            int y = m["y"].asInt() / TILE_SIZE;
            (builder->*func)(x, y);
        }
        return;
    }

  public:
    ZLevelFactory(Layer* l, StoryFactory* sf, std::function<void()> cb) :
            layer(l), storyFactory(sf), levelDoneCallback(cb) { }

    virtual Level* createLevel(int stage) {
        TMXTiledMap* map = TMXTiledMap::create(stageFileNames[stage]);
        layer->addChild(map, 0);

        Size s = Director::getInstance()->getWinSize();
        Size mapSize = map->getMapSize();
        setInitialPoint(0, s.height - mapSize.height * TILE_SIZE);
        map->setPosition(initialX, initialY);

        ZObjectFactory* objFactory = new ZObjectFactory(layer,
                                                        initialX, initialY);
        ZLevelBuilder builder(objFactory);
        builder.setSize(mapSize.width, mapSize.height);
        buildPoints(&builder, &ZLevelBuilder::setHeroPos, map, "SpawnPoint");
        buildPoints(&builder, &ZLevelBuilder::addBall, map, "Balls");
        buildPoints(&builder, &ZLevelBuilder::addHouse, map, "Houses");

        TMXLayer* walls = map->getLayer("WallLayer");
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
        builder.setStoryFactory(storyFactory);
        builder.setLevelDoneCallback(levelDoneCallback);
        Level *level = builder.build();
        return level;
    }
};

const char* ZLevelFactory::stageFileNames[] = {"stage1.tmx", "stage1.tmx"};

};

#endif
