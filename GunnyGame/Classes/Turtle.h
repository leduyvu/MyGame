//
//  Turtle.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/15.
//
//

#ifndef __GunnyGame__Turtle__
#define __GunnyGame__Turtle__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class Turtle : public CCObject{
public:
    Turtle();
    ~Turtle();
    void create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint);
    void running();
    CCSprite* getSprite();
private:
    CCPoint startPoint;
    CCPoint endPoint;
    bool checkrunning = false;
    CCSprite* turtle;
};

#endif /* defined(__GunnyGame__Turtle__) */
