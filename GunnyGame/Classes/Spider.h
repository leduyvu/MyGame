//
//  Spider.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/10.
//
//

#ifndef __GunnyGame__Spider__
#define __GunnyGame__Spider__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class Spider : public CCObject{
public:
    Spider();
    ~Spider();
    void create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint);
    void running();
    CCSprite* getSprite();
private:
    CCPoint startPoint;
    CCPoint endPoint;
    bool checkrunning = false;
    CCSprite* spider;
};

#endif /* defined(__GunnyGame__Spider__) */
