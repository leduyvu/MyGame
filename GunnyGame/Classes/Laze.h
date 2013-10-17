//
//  Laze.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/17.
//
//

#ifndef __GunnyGame__Laze__
#define __GunnyGame__Laze__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class Laze : public CCObject{
public:
    Laze();
    ~Laze();
    void create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint);
    void running();
    CCSprite* getSprite();
private:
    CCPoint startPoint;
    CCPoint endPoint;
    bool checkrunning = false;
    CCSprite* laze;
};
#endif /* defined(__GunnyGame__Laze__) */
