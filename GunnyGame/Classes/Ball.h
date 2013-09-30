//
//  Ball.h
//  GunnyGame
//
//  Created by macbook_006 on 13/09/30.
//
//

#ifndef __GunnyGame__Ball__
#define __GunnyGame__Ball__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class Ball : public cocos2d::CCNode{
public:
    Ball();
    ~Ball();
    void createBall(b2World * world, string str, CCPoint location);
    void throwBall(b2Vec2 vector);
    void setLocation(CCPoint location);

    CCPoint getLocation();
    CCSprite* getSprite();
    b2Body* getBody();
private:
    PhysicsSprite* sprBall;
    b2Body *body;
    CCPoint location;
    
};

#endif /* defined(__GunnyGame__Ball__) */
