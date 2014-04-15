//
//  GameScene.h
//  pushpush
//
//  Created by June The Pain on 2014. 4. 14..
//
//

#ifndef pushpush_GameScene_h
#define pushpush_GameScene_h

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
};

#endif
