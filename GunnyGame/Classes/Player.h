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

USING_NS_CC;
using namespace std;
class Player : public cocos2d::CCNode {
public:
    Player();
    ~Player();
    void createPlayer(string str, CCPoint location);
    void movingPlayer(CCPoint location);
    void throwPlayer(CCPoint location);
    CCPoint getLocation();
    CCSprite* getSprite();
private:
    CCSprite* sprPlayer;
    CCPoint location;
    
};
#endif /* defined(__GunnyGame__Player__) */
