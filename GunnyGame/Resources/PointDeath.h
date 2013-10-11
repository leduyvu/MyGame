//
//  PointDeath.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/11.
//
//

#ifndef __GunnyGame__PointDeath__
#define __GunnyGame__PointDeath__

#include <iostream>
#include "cocos2d.h"
#include <b2Math.h>
#include "PhysicsSprite.h"
USING_NS_CC;
using namespace std;
class PointDeath : public CCObject{
public:
    PointDeath();
    ~PointDeath();
    void create(CCPoint start, CCPoint end);
    bool getLife();
    void setLife();
    bool checkLocation(CCPoint location);
    CCPoint getStartPoint();
    CCPoint getEndPoint();
private:
    CCPoint start;
    CCPoint end;
    bool life;
};

#endif /* defined(__GunnyGame__PointDeath__) */
