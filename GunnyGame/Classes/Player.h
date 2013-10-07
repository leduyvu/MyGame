//
//  Player.h
//  GunnyGame
//
//  Created by macbook_006 on 13/09/30.
//
//

#ifndef __GunnyGame__Player__
#define __GunnyGame__Player__

#include <iostream>
#include "cocos2d.h"
#include "PhysicsSprite.h"

USING_NS_CC;
using namespace std;
class Player : public cocos2d::CCObject {
public:
    Player();
    ~Player();
    void createPlayer(b2World * world, string str, CCPoint location);
    void movingPlayer(CCPoint location);
    void throwPlayer(CCLayer* layer, CCPoint location);
    CCPoint getLocation();
    CCSprite* getSprite();
    void setLocation(CCPoint p);
private:
    PhysicsSprite* sprPhysicPlayer;
    b2Body* body;
    CCSprite* sprPlayer;
    CCPoint location;
    
};
#endif /* defined(__GunnyGame__Player__) */
