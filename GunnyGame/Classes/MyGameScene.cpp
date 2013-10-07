//
//  MyGameScene.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/09/19.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "PhysicsSprite.h"
#include "MyGameScene.h"
#include "SimpleAudioEngine.h"
#include "PhysicsSprite.h"
#include "math.h"
#include "Player.h"
#include "Ball.h"
#include "Boot.h"
USING_NS_CC;
MyGame::MyGame()
{
    MyGame::init();
    this->initPhysics();
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
//==================map=============
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("mapGunny2.tmx");
    //setup Body where is mapWall
    _background = _tileMap->layerNamed("mapWall");
    CCSize layerSize = _background->getLayerSize();
    for( int y=0; y < layerSize.height; y++ )
    {
        for( int x=0; x < layerSize.width; x++ )
        {
            CCSprite* tileSprite = _background->tileAt(ccp(x, y));
            if( tileSprite )
            {
                //create static-Body
                this->createRectangularFixture(_background, x, y, 1.0f, 1.0f);
            }
        }
    }
    map->addChild(_tileMap);
    this->addChild(map);
//=====================

//====================add Player =================
    this->player->createPlayer(this->world, "nembong1.png", ccp(20, 150));
    this->addChild(player->getSprite(),9);
    player->getSprite()->setScale(0.3);
    player->getSprite()->runAction(CCMoveBy::create(4, ccp(300,0)));
//================================================

//========== Shoot power =========================
    CCSprite *timer = CCSprite::create("bt_progressbar1.png");
    timer->setAnchorPoint(ccp(0, 0));
    timerBar = CCProgressTimer::create(timer);
    timerBar->setType(kCCProgressTimerTypeBar);
    timerBar->setAnchorPoint(ccp(0, 0));
    timerBar->setPosition(0, 0);
    timerBar->setMidpoint(ccp(0,0));
    timerBar->setBarChangeRate(ccp(1, 0));
    this->addChild(timerBar, 10);
    timerBar->setPercentage(0);
//=================================================
    
//======================= BALL =========================
//    this->ball = new Ball();
//    ball->createBall(world, "bong1.png", player->getLocation());
//    this->addChild(this->ball->getPhysicsSprite(),10);
//========================================================
    
//=============== road ================================
    rf = new RoadTransfer();
    rf->createRoad(world, ccp(370, 400));
    this->addChild(rf,9);
    CCLOG("Ball ,%f - %f", rf->getSprite()->getPosition().x, rf->getSprite()->getPosition().x);

//=====================================================
    scheduleUpdate();
    this->schedule(schedule_selector(MyGame::runBoot), 2.55);
    this->schedule(schedule_selector(MyGame::impactBall));
}

MyGame::~MyGame()
{
    delete world;
    world = NULL;
}

bool MyGame::init(){
    map = new CCLayer();
    arrWall = new CCArray();
    arrBalls = new CCArray();
    this->swipeRecognized = false;
    this->spriteContained = false;
    this->swiping = false;
    
    this->player = new Player();
    this->checkRoad = false;
    this->deltaTime = 0;
    this->checkRunAnimation = false;
    this->transfer = false;
    this->boom = false;
    this->checkRun = false;
    this->touchBool = false;
    this->time = 0;
    this->throwBalls = new PhysicsSprite();
    return true;
}
void MyGame::initPhysics()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);;
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    world->SetContinuousPhysics(true);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    // Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom
    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/32,0));
    groundBody->CreateFixture(&groundBox,0);

//    // top
//    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
//    groundBody->CreateFixture(&groundBox,0);

    // left
//    groundBox.Set(b2Vec2(0,s.height/32), b2Vec2(0,0));
//    groundBody->CreateFixture(&groundBox,0);

    // right
//    groundBox.Set(b2Vec2(s.width/32,s.height/32), b2Vec2(s.width/32,0));
//    groundBody->CreateFixture(&groundBox,0);
}

void MyGame::draw()
{
    CCLayer::draw();
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    world->DrawDebugData();

    kmGLPopMatrix();
}

void MyGame::addNewSpriteAtPosition(CCPoint p){
   
}

void MyGame::update(float dt)
{
    setViewPointCenter(player->getSprite()->getPosition());
    
//    this->player->getSprite()->setPosition(ccp(this->getPosition().x + 850,this->getPosition().y + 150));
    CCNode *ex = this->getChildByTag(222);
    if(ex != NULL && ex->getChildByTag(1120) != NULL &&  ex->getChildByTag(1120)->getPosition().x < 50)
        ex->removeChildByTag(1120);
    if(touchBool)
    {
        time = time + dt;
        timerBar->setPercentage(5 + time * 50);
    }
    if(checkRun && !checkRunAnimation)
    {
        this->runAction(CCSequence::create(
                                           CCCallFunc::create(this, callfunc_selector(MyGame::runAnimation)),
                                           CCDelayTime::create(1.6),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::throwBall)),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::showShooter)),
                                           NULL));
        checkRun = false;
        boom = true;
    }
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);

    //Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * 32, b->GetPosition().y * 32) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
}

void MyGame::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    time = 0;
    CCSetIterator it;
    CCTouch *touch = (CCTouch*)touches->anyObject();
    this->touchBegin = this->getParent()->convertTouchToNodeSpace(touch);
    CCLOG("touch Begin : %f - %f", touchBegin.x, touchBegin.y);
    CCLOG("this : %f - %f", this->getPosition().x, this->getPosition().y);

    if(fabs(touchBegin.x - player->getSprite()->getPosition().x) < 100 && fabs(touchBegin.y - player->getSprite()->getPosition().y) < 100)
    {
        transfer = true;
        touchBool = false;
        swipeRecognized = false;
        spriteContained = true;
    }
    else  if(!checkRunAnimation)
    {
        touchBool = true;
        transfer = false;
    }
}

void MyGame::ccTouchesMoved (CCSet *touches, CCEvent *event) {
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    if(transfer)
    {
        if(touchLoc.x > touchBegin.x && touchBegin.x > 0)
        {
            //player->getSprite()->runAction(CCMoveBy::create(1, ccp(90,0)));
            //mapPosition(ccp(-90,0));
           // player->movingPlayer(ccp(-90,0));
            transfer = false;
            touchBegin = ccp(0,0);

        }
        else if(touchLoc.x < touchBegin.x && touchBegin.x > 0)
        {
            //player->getSprite()->runAction(CCMoveBy::create(1, ccp(-90,0)));
            //mapPosition(ccp(90,0));
            //player->movingPlayer(ccp(90,0));
            transfer = false;
            touchBegin = ccp(0,0);
        }
    }
    
    
//    
//    //version23
//        if (spriteContained) {
//            CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
//            movingSwipePoint = touchLoc;
//            
//            if (!swipeRecognized) swiping = true;
//            else swiping = false;
//            
//            if (swiping == true) {
//                CCRect touchRect = CCRect(touchLoc.x, touchLoc.y, 40, 40);
//                
//                CCRect swipeRightRect = CCRectMake((touchBegin.x + 32), touchBegin.y, 80, 20);
//                CCRect swipeLeftRect = CCRectMake((touchBegin.x - 32), touchBegin.y, 80, 20);
//                CCRect swipeUpRect = CCRectMake(touchBegin.x, touchBegin.y + (32), 20, 80);
//                CCRect swipeDownRect = CCRectMake(touchBegin.x, touchBegin.y - (32), 20, 80);
//                if ((movingSwipePoint.x - touchBegin.x > 32) && touchRect.intersectsRect(swipeRightRect)){
//                    swipeRecognized = true;
//                    swipeRight = true;
//                }
//                else if ((touchBegin.x - movingSwipePoint.x > 32) && touchRect.intersectsRect(swipeLeftRect)) {
//                    swipeRecognized = true;
//                    swipeLeft = true;
//                }
//                else if ((movingSwipePoint.y - touchBegin.y > 32) && touchRect.intersectsRect(swipeUpRect)) {
//                    swipeRecognized = true;
//                    swipeUp = true;
//                }
//                else if ((touchBegin.y - movingSwipePoint.y > 32) && touchRect.intersectsRect(swipeDownRect)) {
//                    swipeRecognized = true;
//                    swipeDown = true;
//                }
//
//            }
//        }

    
}

void MyGame::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    if(!checkRunAnimation)
    {
        CCSetIterator it;
        CCTouch* touch;
        for( it = touches->begin(); it != touches->end(); it++)
        {
            touch = (CCTouch*)(*it);
            if(!touch)
                break;
            location = touch->getLocationInView();
            location = CCDirector::sharedDirector()->convertToGL(location);
        }
        if(!checkRun && touchBool)
        {
            checkRun = true;
        }
        touchBool = false;
    }
}

CCScene* MyGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new MyGame();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

void MyGame::createRectangularFixture(CCTMXLayer* layer, int x, int y,
                                          float width, float height)
{
    // get position & size
    CCPoint p = layer->positionAt(ccp(x,y));
    CCSize tileSize = this->_tileMap->getTileSize();
    const float pixelsPerMeter = 32.0f;
    
    // create the body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set((p.x + (tileSize.width / 2.0f))/pixelsPerMeter,
                         (p.y + (tileSize.height / 2.0f))/pixelsPerMeter);
    b2Body *body = world->CreateBody(&bodyDef);
    body->SetAngularDamping(33);
    // define the shape
    b2PolygonShape shape;
    shape.SetAsBox((tileSize.width / pixelsPerMeter) * 0.5f * width,
                   (tileSize.width / pixelsPerMeter) * 0.5f * height);
    
    // create the fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.0f;
    //    fixtureDef.filter.categoryBits = kFilterCategoryLevel;
    fixtureDef.filter.maskBits = 0xffff;
    body->CreateFixture(&fixtureDef);
}

void MyGame::runAnimation()
{
    checkRunAnimation = true;
    this->player->getSprite()->setVisible(false);
    this->player->throwPlayer(this, player->getSprite()->getPosition());
}

void MyGame::runBoot(float delta)
{
    deltaTime = deltaTime + delta;
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("quaivat.plist");
    CCArray* animFrames = new CCArray;
    animFrames->autorelease();
    char str[100] = {0};
    for(int i = 1; i < 6; i++) {
        sprintf(str, "no%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.4);
    CCSprite *popSprite = CCSprite::create();
    //popSprite->setScale();
    animation->setLoops(7);
    
    popSprite->setPosition(ccp(150 + deltaTime* 20, 150));
    animation->setLoops(1);
    this->addChild(popSprite, 28);
    popSprite->runAction(CCSequence::create(CCAnimate::create(animation),
                                            CCRemoveSelf::create(),
                                            NULL));
    
}


void MyGame::throwBall()
{
    Ball *ball = new Ball();
    ball->createBall(this->world, "bong1.png", player->getSprite()->getPosition());
    this->addChild(ball, 10);
    
    float prercent = timerBar->getPercentage();
    float X = location.x + this->getPosition().x - this->player->getSprite()->getPosition().x;
    float Y = location.y - this->player->getSprite()->getPosition().y;
    float x = prercent/4 * X/(sqrt(X * X + Y * Y));
    float y = prercent/4 * Y/(sqrt(X * X + Y * Y));
    CCLOG("player * %f , ... %f ",player->getSprite()->getPosition().x, player->getSprite()->getPosition().y);
    CCLOG("touches  * %f .. %f ", location.x, location.y);
    b2Vec2 ex = b2Vec2();
    ex.Set(x, y);
    ball->throwBall(ex);
    time = 0;
    arrBalls->addObject(ball);
}
void MyGame::showShooter()
{
    this->player->getSprite()->setVisible(true);
    checkRunAnimation = false;
    timerBar->setPercentage(0);
}


void MyGame::createDynamicFixture(CCTMXLayer* layer, int x, int y,
                                      float width, float height)
{
    
}
void MyGame::impactBall(){
    CCObject *obj;
    CCARRAY_FOREACH(this->arrBalls, obj)
    {
        Ball* ball = dynamic_cast<Ball*>(obj);
        if(ball != NULL && ball->getBody()->GetPosition().y > 350/32 && ball->getBody()->GetPosition().y < 440/32 && ball->getBody()->GetPosition().x > 330/32 && ball->getBody()->GetPosition().y < 410/32)
        {
            rf->getBody()->SetGravityScale(10);
           // this->runAction(CCMoveTo::create(1, ccp(90,0)));
            //player->movingPlayer(ccp(90,0));
            arrBalls->removeAllObjects();
            setViewPointCenter(player->getSprite()->getPosition());
        }
        if(ball->getBody()->GetPosition().y *32 < 10 && ball->getBody()->GetPosition().x *32 < 700)
        {
            arrBalls->removeObject(ball);
            this->removeChild(ball);
            ball->autorelease();
        }
    }
}

void MyGame::mapPosition(CCPoint point){
    //this->runAction(CCMoveBy::create(1, point));
    this->setPosition(player->getSprite()->getPosition());
}

void MyGame::setViewPointCenter(CCPoint position) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    CCPoint actualPosition = ccp(x, y);
    CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}