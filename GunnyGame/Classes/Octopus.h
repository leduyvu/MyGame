//
//  Octupus.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/21.
//
//

#ifndef __GunnyGame__Octopus__
#define __GunnyGame__Octopus__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class Octopus : public CCObject{
public:
    Octopus();
    ~Octopus();
    void create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint);
    void running();
    CCSprite* getSprite();
private:
    CCPoint startPoint;
    CCPoint endPoint;
    bool checkrunning = false;
    CCSprite* octopus;
};
#endif /* defined(__GunnyGame__Octopus__) */
