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
#include "PointDeath.h"
USING_NS_CC;
MyGame::MyGame()
{
    MyGame::init();
    this->initPhysics();
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
//==================map=============
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("mapGame2.tmx");
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
//================================================

    
//====================add point death ===================
    PointDeath * pd1 = new PointDeath();
    pd1->create(ccp(704, 120), ccp(960,120));
    arrPointDeath->addObject(pd1);
    
    PointDeath * pd2 = new PointDeath();
    pd2->create(ccp(1760, 120), ccp(2080,120));
    arrPointDeath->addObject(pd2);
    
    PointDeath * pd3 = new PointDeath();
    pd3->create(ccp(2530, 120), ccp(2810,120));
    arrPointDeath->addObject(pd3);
//================================================
//====================add Player =================
    this->player->createPlayer(this->world, "nembong1.png", ccp(90, 120));
    this->addChild(player->getSprite(),9);
    player->getSprite()->setScale(0.3);
    //player->getSprite()->runAction(CCMoveBy::create(4, ccp(300,0)));
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
    
//=============== road ================================
    CCObject *object;
    CCARRAY_FOREACH(arrPointDeath, object){
        PointDeath* pd = dynamic_cast<PointDeath*>(object);
        RoadTransfer* rf = new RoadTransfer();
        rf->createRoad(world, ccp((pd->getEndPoint().x + pd->getStartPoint().x)/2, 400), 8);
        this->addChild(rf,9);
        arrWall->addObject(rf);
        
//        CCLOG("Ball ,%f - %f", roadTransfer->getSprite()->getPosition().x, roadTransfer->getSprite()->getPosition().x);

    }
    
//    roadTransfer = new RoadTransfer();
//    roadTransfer->createRoad(world, ccp(830, 400), 8);
//    this->addChild(roadTransfer,9);
//    CCLOG("Ball ,%f - %f", roadTransfer->getSprite()->getPosition().x, roadTransfer->getSprite()->getPosition().x);

//=====================================================
    scheduleUpdate();
    //this->schedule(schedule_selector(MyGame::runBoot), 2.55);
    this->schedule(schedule_selector(MyGame::impactBall));
    this->schedule(schedule_selector(MyGame::runningSpider), 1);
}

MyGame::~MyGame()
{
    delete world;
    world = NULL;
}

bool MyGame::init(){
    arrPointDeath = new CCArray();
    spiders = new CCArray();
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
    listener = new MyContactListener();
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);;
    // Do we want to let bodies sleep?
    world->SetContactListener(listener);
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
    CCLOG("player .x  %f ", player->getSprite()->getPosition().x);
    CCObject *object;
    CCARRAY_FOREACH(arrPointDeath, object){
        PointDeath* pd = dynamic_cast<PointDeath*>(object);
        if(pd->checkLocation(player->getSprite()->getPosition()) && !pd->getLife()){
            player->getSprite()->runAction(CCSequence::create(CCMoveBy::create(2, ccp(0,-300)),
                                                              CCCallFunc::create(this, callfunc_selector(MyGame::setPositionAgian)),
                                                              NULL));
//            player->getSprite()->setPosition(ccp(150 - this->getPosition().x, 150 - this->getPosition().y));
            return;
        }
    }
    
    setViewPointCenter(player->getSprite()->getPosition());
    timerBar->setPosition(this->getPosition());
    timerBar->getSprite()->setPosition(this->getPosition());

    CCNode *ex = this->getChildByTag(222);
    if(ex != NULL && ex->getChildByTag(1120) != NULL &&  ex->getChildByTag(1120)->getPosition().x < 50)
        ex->removeChildByTag(1120);
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
    if(boolAnimaon)
    {
        if(swipeRight && swipeUp)
        {
            this->setTouchEnabled(false);
            touchBool = false;
            checkRun = false;
            swipeRight =false;
            swipeUp = false;
            moving = true;
            player->getSprite()->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(100, 100)),
                                                              CCMoveBy::create(0.15, ccp(10, 0)),
                                                              CCMoveBy::create(0.5, ccp(100, -100)),
                                                              CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
                                                              NULL));
        }
        else if(swipeLeft && swipeUp)
        {
            this->setTouchEnabled(false);
            touchBool = false;
            checkRun = false;
            swipeLeft =false;
            swipeUp = false;
            moving = true;
            player->getSprite()->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(-100, 100)),
                                                              CCMoveBy::create(0.15, ccp(-10, 0)),
                                                              CCMoveBy::create(0.5, ccp(-100, -100)),
                                                              CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
                                                              NULL));
        }
        else if(swipeRight)
        {
            this->setTouchEnabled(false);
            touchBool = false;
            checkRun = false;
            swipeRight = false;
            moving = true;
            player->getSprite()->runAction(CCSequence::create(CCMoveBy::create(1, ccp(150, 0)),
                                                              CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
                                                              NULL));
        }
        else if(swipeLeft)
        {
            this->setTouchEnabled(false);
            touchBool = false;
            checkRun = false;
            swipeLeft = false;
            moving = true;
            player->getSprite()->runAction(CCSequence::create(CCMoveBy::create(1, ccp(-150, 0)),
                                                              CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
                                                              NULL));
        }
    }
    if(touchBool)
    {
        time = time + dt;
        timerBar->setPercentage(5 + time * 50);
    }
    if(timerBar->getPercentage() > 30 && checkRun && !checkRunAnimation && boolAnimaon && !moving)
    {
        this->runAction(CCSequence::create(
                                           CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::runAnimation)),
                                           CCDelayTime::create(1.6),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::throwBall)),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::showShooter)),
                                           NULL));
        checkRun = false;
        boom = true;
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

    if((fabs(touchBegin.x - this->getPosition().x - player->getSprite()->getPosition().x) < 200 && fabs(touchBegin.y - player->getSprite()->getPosition().y) < 200) || touchBegin.y < 250)
    {
        transfer = true;
        touchBool = false;
        swipeRecognized = false;
        spriteContained = true;
    }
    else  if(!checkRunAnimation && !moving)
    {
        touchBool = true;
        transfer = false;
    }
}

void MyGame::ccTouchesMoved (CCSet *touches, CCEvent *event) {
    CCTouch *touch = (CCTouch*)touches->anyObject();
    if (transfer) {
        CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
        movingSwipePoint = touchLoc;
        
        if (!swipeRecognized) swiping = true;
        else swiping = false;
        
        if (swiping == true) {
            CCRect touchRect = CCRect(touchLoc.x, touchLoc.y, 70, 70);
            
            CCRect swipeRightRect = CCRectMake((touchBegin.x + 40), touchBegin.y, 80, 40);
            CCRect swipeLeftRect = CCRectMake((touchBegin.x - 40), touchBegin.y, 80, 40);
            CCRect swipeUpRect = CCRectMake(touchBegin.x, touchBegin.y + (40), 40, 80);
            CCRect swipeDownRect = CCRectMake(touchBegin.x, touchBegin.y - (40), 40, 80);
            
            if ((movingSwipePoint.x - touchBegin.x > SWIPE_DISTANCE) && touchRect.intersectsRect(swipeRightRect)) {
                swipeRecognized = true;
                swipeRight = true;
                CCLOG("1");
            }
            else if ((touchBegin.x - movingSwipePoint.x > SWIPE_DISTANCE) && touchRect.intersectsRect(swipeLeftRect)) {
                swipeRecognized = true;
                swipeLeft = true;
                CCLOG("2");
            }
            else if ((movingSwipePoint.y - touchBegin.y > SWIPE_DISTANCE) && touchRect.intersectsRect(swipeUpRect)) {
                if(movingSwipePoint.x - touchBegin.x > 3)
                {
                    swipeRight = true;
                    CCLOG("1");
                }
                else if (touchBegin.x - movingSwipePoint.x > 3)
                {
                    swipeLeft = true;
                    CCLOG("2");
                }
                swipeRecognized = true;
                swipeUp = true;
                CCLOG("3");
            }
            else if ((touchBegin.y - movingSwipePoint.y > SWIPE_DISTANCE) && touchRect.intersectsRect(swipeDownRect)) {
                if(movingSwipePoint.x - touchBegin.x > 0)
                {
                    swipeRight = true;
                    CCLOG("1");
                }
                else if (touchBegin.x - movingSwipePoint.x > 0)
                {
                    swipeLeft = true;
                    CCLOG("2");
                }
                swipeRecognized = true;
                swipeDown = true;
                CCLOG("4");
            }
            else if (!touchRect.intersectsRect(swipeRightRect) && !touchRect.intersectsRect(swipeLeftRect)
                     && !touchRect.intersectsRect(swipeUpRect) && !touchRect.intersectsRect(swipeDownRect))
            {
                swipeRecognized = true;
                CCLOG("5");
            }
        }
    }

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

void MyGame::createDynamicFixture(CCTMXLayer* layer, int x, int y,
                                      float width, float height)
{
    // get position & size
    CCPoint p = layer->positionAt(ccp(x,y));
    CCSize tileSize = this->_tileMap->getTileSize();
    const float pixelsPerMeter = 32.0f;
    
    // create the body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((p.x + (tileSize.width / 2.0f))/pixelsPerMeter,
                         (p.y + (tileSize.height / 2.0f))/pixelsPerMeter);
    b2Body *body = world->CreateBody(&bodyDef);
    body->SetGravityScale(0);
    // define the shape
    b2PolygonShape shape;
    shape.SetAsBox((tileSize.width / pixelsPerMeter) * 0.5f * width,
                   (tileSize.width / pixelsPerMeter) * 0.5f * height);
    
    // create the fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 100;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.0f;
    //    fixtureDef.filter.categoryBits = kFilterCategoryLevel;
    //fixtureDef.filter.maskBits = 0xffff;
    body->CreateFixture(&fixtureDef);
    body->GetFixtureList()->SetSensor(false);
}


void MyGame::runAnimation()
{
    this->setTouchEnabled(false);
    boolAnimaon = false;
    player->pauseSchedulerAndActions();
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
    this->addChild(ball, 20);
    
    float prercent = timerBar->getPercentage();
    float X = location.x - this->getPosition().x - this->player->getSprite()->getPosition().x;
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
    this->setTouchEnabled(true);
    this->player->getSprite()->setVisible(true);
    checkRunAnimation = false;
    timerBar->setPercentage(0);
    player->resumeSchedulerAndActions();
    boolAnimaon = true;
}

void MyGame::impactBall(){
    CCObject *obj;
    CCARRAY_FOREACH(this->arrBalls, obj)
    {
        Ball* ball = dynamic_cast<Ball*>(obj);
        if(ball->getBody()->GetPosition().y *32 < 90)
        {
            arrBalls->removeObject(ball);
            this->removeChild(ball);
            ball->autorelease();
        }
        MyContactListener* listenImpact = dynamic_cast<MyContactListener*>(listener);
        if(listenImpact->getResult())
        {
            listenImpact->setResult(false);
            if(arrPointDeath->count() > 0){
                arrPointDeath->removeObjectAtIndex(0);
            }
            world->DestroyBody(ball->getBody());
            arrBalls->removeAllObjects();
            //this->removeChild(ball);
            Spider* spider = new Spider();
            spider->create(this->world, "connhen.png",
                           ccp(this->getPosition().x + 50, this->getPosition().y + 70),
                           ccp(200,200),
                           ccp(500, 200));
            this->addChild(spider->getSprite(), 10);
            spiders->addObject(spider);
        }
    }
}

void MyGame::runningSpider()
{
    CCObject *objSpider;
    CCARRAY_FOREACH(this->spiders, objSpider){
        Spider* spider = dynamic_cast<Spider*>(objSpider);
        if(spider != NULL)
            spider->running();
    }
}

void MyGame::mapPosition(CCPoint point){
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
void MyGame::relaxMoving(){
    this->setTouchEnabled(true);
    swipeRight = false;
    swipeLeft = false;
    swipeUp = false;
    swipeDown = false;
    swipeRight = false;
    transfer = false;
    touchBool = false;
    moving = false;
}

void  MyGame::setPositionAgian()
{
    CCPoint p = ccp(120 - this->getPosition().x, 120);
    this->removeChild(player->getSprite());
    player->getSprite()->setPosition(p);
    this->addChild(player->getSprite(),10);

}