//
//  boot.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/01.
//
//

#ifndef __GunnyGame__Boot__
#define __GunnyGame__Boot__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class Boot : public PhysicsSprite{
public:
    Boot();
    ~Boot();
    void createBoot(CCLayer* layer, b2World * world, string str, CCPoint location);
    void setLocation(CCPoint location);
    
    CCPoint getLocation();
    CCSprite* getSprite();
    b2Body* getBody();
    PhysicsSprite* getPhysicsSprite();
    void running(CCLayer* layer);
private:
    PhysicsSprite* sprPhysicsBoot;
    CCSprite* sprBoot;
    b2Body *body;
    CCPoint location;
    
};

#endif /* defined(__GunnyGame__Boot__) */
