//
//  File.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/10.
//
//

#ifndef __GunnyGame__TopScreen__
#define __GunnyGame__TopScreen__

#include <iostream>
#include "cocos2d.h"
#include "curl.h"

using namespace  cocos2d;
USING_NS_CC;

class TopScreen :public CCLayer {
private:
    CCSize _screenSize;
    CCSprite *_topScreen;
    
public:
    virtual bool init();
    static CCScene * scene();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *event);
    CREATE_FUNC(TopScreen);
};

#endif /* defined(__GunnyGame__File__) */
