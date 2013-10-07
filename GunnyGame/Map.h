//
//  Map.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/07.
//
//

#ifndef __GunnyGame__Map__
#define __GunnyGame__Map__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"
#include "RoadTransfer.h"
#include "PhysicsSprite.h"
#include "Player.h"
#include "Ball.h"
USING_NS_CC;
class MyGame : public cocos2d::CCLayer {
public:
    ~MyGame();
    MyGame();
    bool init();
    void createRectangularFixture(CCTMXLayer* layer, int x, int y,
                                  float width, float height);
    
private:
    CCSprite *sprite;
    CCTMXLayer *_background, *_background1;
    CCTMXTiledMap *_tileMap;
    b2World* world;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref

    
};
#endif /* defined(__GunnyGame__Map__) */
