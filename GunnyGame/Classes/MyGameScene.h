//
//  MyGameScene.h
//  GunnyGame
//
//  Created by macbook_006 on 13/09/19.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
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
    // returns a Scene that contains the MyGame as the only child
    static cocos2d::CCScene* scene();
    
    void initPhysics();
    // adds a new sprite at a given coordinate
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    virtual void draw();
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void update(float dt);
    
    void addShooter();
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesMoved (CCSet *touches, CCEvent *event);
    void createRectangularFixture(CCTMXLayer* layer, int x, int y,
                                  float width, float height);
    void createDynamicFixture(CCTMXLayer* layer, int x, int y,
                              float width, float height);
    void runAnimation();
    void throwBall();
    void showShooter();
    void runBoot(float delta);
    void impactBall();
    void mapPosition(CCPoint point);
    void setViewPointCenter(CCPoint position);
    
private:
    
    CCLayer *map;
    CCPoint movingSwipePoint;
    bool swipeRecognized = false;
    bool spriteContained = false;
    bool swiping = false;
    bool swipeRight;
    bool swipeLeft;
    bool swipeUp;
    bool swipeDown;
    CCArray* arrBalls, *arrWall;
    Ball* ball;
    Player *player;
    bool checkRoad;
    CCSprite* road;
    float deltaTime = 0;
    bool checkRunAnimation = false;
    bool transfer = false;
    CCPoint touchBegin;
    bool boom = false;
    CCSprite *sprite;
    CCTMXLayer *_background, *_background1;
    CCTMXTiledMap *_tileMap;
    bool checkRun = false;
    bool touchBool = false;
    float time = 0;
    CCPoint location;
    CCProgressTimer* timerBar;
    b2World* world;
    b2World* wall;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    cocos2d::CCTexture2D* textture; // weak ref
    PhysicsSprite *throwBalls = new PhysicsSprite();
    RoadTransfer *rf;

};

#endif // __HELLO_WORLD_H__
