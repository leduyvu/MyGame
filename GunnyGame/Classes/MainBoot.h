//
//  MainBoot.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/21.
//
//

#ifndef __GunnyGame__MainBoot__
#define __GunnyGame__MainBoot__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class MainBoot : public CCObject{
public:
    MainBoot();
    ~MainBoot();
    void create(string str, CCPoint location, bool life);
    void running();
    CCSprite* getSprite();
    void setLoction(int location);
    int getLoction();
    void setLife(bool life);
private:
    bool runLeft = true;
    bool life = true;
    int location = 1;
    CCSprite* mainBoot;
};
#endif /* defined(__GunnyGame__MainBoot__) */
