//
//  RoadTransfer.h
//  GunnyGame
//
//  Created by macbook_006 on 13/09/25.
//
//

#ifndef __GunnyGame__RoadTransfer__
#define __GunnyGame__RoadTransfer__

#include <iostream>
#include "cocos2d.h"
#include "PhysicsSprite.h"
USING_NS_CC;
class RoadTransfer : public PhysicsSprite {
public:
    ~RoadTransfer();
    RoadTransfer();
    void createRoad(b2World* world, CCPoint point);
    void swivelBar(int degree);
    CCSprite* getSprite();
    void setScales(b2World* world);
private:
    CCSprite* roadBar;
    CCPoint location;
    b2Body* body;
    
};

#endif /* defined(__GunnyGame__RoadTransfer__) */
