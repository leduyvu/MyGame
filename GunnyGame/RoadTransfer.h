//
//  RoadTransfer.h
//  GunnyGame
//
//  Created by macbook_006 on 13/09/25.
//
//

#ifndef __GunnyGame__RoadTransfer__
#define __GunnyGame__RoadTransfer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class RoadTransfer : public cocos2d::CCLayer {
public:
    ~RoadTransfer();
    RoadTransfer();
    void createBar(CCPoint point);
    void swivelBar(int degree);
    CCSprite* getSprite();
private:
    CCSprite* roadBar;
    CCPoint location;
    
};

#endif /* defined(__GunnyGame__RoadTransfer__) */
