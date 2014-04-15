//
//  GameScene.cpp
//  pushpush
//
//  Created by June The Pain on 2014. 4. 15..
//
//

#include "GameScene.h"
using namespace cocos2d;
CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    return true;
}