//
//  Arrow.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/21.
//
//

#ifndef __GunnyGame__Arrow__
#define __GunnyGame__Arrow__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class Arrow : public CCObject{
public:
    Arrow();
    ~Arrow();
    void create(string str, CCPoint location, bool life);
    void running();
    CCSprite* getSprite();
    void particle();
private:
    CCSprite* arrow;
};

#endif /* defined(__GunnyGame__Arrow__) */
