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
class Player : public PhysicsSprite{
public:
    Player();
    ~Player();
    void createPlayer(b2World * world, string str, CCPoint location);
    void movingPlayer(b2Vec2 ex);
    void throwPlayer(CCLayer* layer, CCPoint location);
    CCSprite* getSprite();
    void setLocation(CCPoint p);
    void setHeart(int heart);
    int getHeart();
private:
    int heart = 100;
    CCSprite* sprPlayer;    
};
#endif /* defined(__GunnyGame__Player__) */
