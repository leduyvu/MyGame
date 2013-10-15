//
//  Bullet.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/15.
//
//

#ifndef __GunnyGame__Bullet__
#define __GunnyGame__Bullet__
#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class Bullet : public CCObject{
public:
    Bullet();
    ~Bullet();
    void create(b2World * world, string str, CCPoint location, bool turnRight);
    void running();
    CCSprite* getSprite();
private:
    bool turnRight;
    bool checkrunning = false;
    CCSprite* bullet;
};

#include <iostream>

#endif /* defined(__GunnyGame__Bullet__) */
