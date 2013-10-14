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
    this->player->createPlayer(this->world, "player.png", ccp(90, 120));
    this->addChild(player, 9);
//    player->getSprite()->setScale(0.3);
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
//    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/32,0));
//    groundBody->CreateFixture(&groundBox,0);

//    // top
//    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
//    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0,s.height/32), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);

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
    player->setPosition(ccp(player->getBody()->GetPosition().x, player->getBody()->GetPosition().y));
//    CCObject *object;
//    CCARRAY_FOREACH(arrPointDeath, object){
//        PointDeath* pd = dynamic_cast<PointDeath*>(object);
//        if(pd->checkLocation(player->getPosition()) && !pd->getLife()){
////            player->getSprite()->runAction(CCSequence::create(CCMoveBy::create(2, ccp(0,-300)),
////                                                              CCCallFunc::create(this, callfunc_selector(MyGame::setPositionAgian)),
////                                                              NULL));
//            return;
//        }
//    }
    
    if(player->getBody()->GetPosition().y * 32 < -150)
    {
        setPositionAgian();
    }
    
    setViewPointCenter(ccp(player->getBody()->GetPosition().x * 32, player->getBody()->GetPosition().y * 32));
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
//            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
    if(touchBool)
    {
        time = time + dt;
        timerBar->setPercentage(5 + time * 50);
    }
    
    if(timerBar->getPercentage() > 30 && checkRun)
    {
        checkRun =false;
        this->runAction(CCSequence::create(
                                           CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::runAnimation)),
                                           CCDelayTime::create(1.6),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::throwBall)),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::showShooter)),
                                           NULL));
    }
    
   
    
    if(boolAnimaon)
    {
//        if(swipeRight && swipeUp)
//        {
//            swiping =false;
//            transfer = false;
//            this->setTouchEnabled(false);
//            touchBool = false;
//            checkRun = false;
//            swipeRight =false;
//            swipeUp = false;
//            moving = true;
//            CCFiniteTimeAction* action1 = CCMoveBy::create(0.5, ccp(100, 100));
//            action1->setTag(1111);
//            
//            CCFiniteTimeAction* action2 = CCMoveBy::create(0.15, ccp(10, 0));
//            action2->setTag(1112);
//
//            CCFiniteTimeAction* action3 = CCMoveBy::create(0.5, ccp(100, -100));
//            action3->setTag(1113);
//            b2Vec2 ex = b2Vec2();
//            ex.Set(7, 10);
//            player->getBody()->SetLinearVelocity(ex);
//            MyGame::relaxMoving();
////
////            player->getSprite()->runAction(CCSequence::create(action1,
////                                                              action2,
////                                                              action3,
////                                                              CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
////                                                              NULL));
//
//
//
//        }
//        else if(swipeLeft && swipeUp)
//        {
//            swiping =false;
//            transfer = false;
//            this->setTouchEnabled(false);
//            touchBool = false;
//            checkRun = false;
//            swipeLeft =false;
//            swipeUp = false;
//            moving = true;
//            CCFiniteTimeAction* action1 = CCMoveBy::create(0.5, ccp(-100, 100));
//            action1->setTag(1121);
//            
//            CCFiniteTimeAction* action2 = CCMoveBy::create(0.15, ccp(-10, 0));
//            action2->setTag(1122);
//            
//            CCFiniteTimeAction* action3 = CCMoveBy::create(0.5, ccp(-100, -100));
//            action3->setTag(1123);
//            b2Vec2 ex = b2Vec2();
//            ex.Set(-7, 10);
//            player->getBody()->SetLinearVelocity(ex);
//            MyGame::relaxMoving();
////            player->getSprite()->runAction(CCSequence::create(action1, action2, action3,
////                                                              CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
////                                                              NULL));
//        }
//        else if(swipeRight)
//        {
//            swiping =false;
//            transfer = false;
//            this->setTouchEnabled(false);
//            touchBool = false;
//            checkRun = false;
//            swipeRight = false;
//            moving = true;
//            CCFiniteTimeAction* action1 = CCMoveBy::create(1, ccp(150, 0));
//            action1->setTag(1131);
//            b2Vec2 ex = b2Vec2();
//            ex.Set(7, 0);
//            player->getBody()->SetLinearVelocity(ex);
//            MyGame::relaxMoving();
////            player->getSprite()->runAction(CCSequence::create(action1,
////                                                              CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
////                                                              NULL));
//        }
//        else if(swipeLeft)
//        {
//            swiping =false;
//            transfer = false;
//            this->setTouchEnabled(false);
//            touchBool = false;
//            checkRun = false;
//            swipeLeft = false;
//            moving = true;
//            CCFiniteTimeAction* action1 = CCMoveBy::create(1, ccp(-150, 0));
//            action1->setTag(1132);
//            b2Vec2 ex = b2Vec2();
//            ex.Set(-7, 10);
//            player->getBody()->SetLinearVelocity(ex);
//            MyGame::relaxMoving();
////            player->getSprite()->runAction(CCSequence::create(action1,
////                                                              CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
////                                                              NULL));
//        }
//    }
//    if(touchBool)
//    {
//        time = time + dt;
//        timerBar->setPercentage(5 + time * 50);
//    }
//    if(timerBar->getPercentage() > 30 && checkRun && !checkRunAnimation && boolAnimaon && !moving)
//    {
//        this->runAction(CCSequence::create(
//                                           CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
//                                           CCCallFunc::create(this, callfunc_selector(MyGame::runAnimation)),
//                                           CCDelayTime::create(1.6),
//                                           CCCallFunc::create(this, callfunc_selector(MyGame::throwBall)),
//                                           CCCallFunc::create(this, callfunc_selector(MyGame::showShooter)),
//                                           NULL));
//        checkRun = false;
//        boom = true;
//    }

    
}
}

void MyGame::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    time = 0;
    CCSetIterator it;
    CCTouch *touch = (CCTouch*)touches->anyObject();
    this->touchBegin = this->getParent()->convertTouchToNodeSpace(touch);
    touchBool = true;
//    CCRect touchRect = CCRect(touchBegin.x, touchBegin.y, 50, 50);
//    CCRect swipeUpRect = CCRectMake(player->getBody()->GetPosition().x * 32, player->getBody()->GetPosition().y * 32 + 40, 20, 60);
    
//    if ((!swiping && touchRect.intersectsRect(swipeUpRect))){
//            b2Vec2 ex = b2Vec2();
//            ex.Set(0, 10);
//            player->movingPlayer(ex);
//            swipeUp = false;
//            transfer = false;
//            touchBool = false;
//  //      return;
//    }
//    
    
    if(touchBegin.y <= 250)
    {
        transfer = true;
        touchBool = false;
        if (touchBegin.x - this->getPosition().x - player->getBody()->GetPosition().x * 32 > 100)
        {
            b2Vec2 ex = b2Vec2();
            float x = touchBegin.x - this->getPosition().x - player->getBody()->GetPosition().x * 32;
            CCLOG("vector  x %f", player->getBody()->GetGravityScale());
            ex.Set(sqrt(0.5 * fabs(x)), 01);
            player->movingPlayer(ex);
        }
        if(player->getBody()->GetPosition().x * 32 - (touchBegin.x - this->getPosition().x) > 100){
            b2Vec2 ex = b2Vec2();
            float x = player->getBody()->GetPosition().x * 32 - (touchBegin.x - this->getPosition().x);
            
            ex.Set(sqrt(0.5 * fabs(x)) * (-1), 01);
            player->movingPlayer(ex);
        }
    }
}

void MyGame::ccTouchesMoved (CCSet *touches, CCEvent *event) {
//    CCTouch *touch = (CCTouch*)touches->anyObject();
//    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
//    movingSwipePoint = touchLoc;
//    CCRect touchRect = CCRect(touchLoc.x, touchLoc.y, 50, 50);
//    CCRect swipeUpRect = CCRectMake(touchBegin.x, touchBegin.y, 60, 120);
//    
//    if ((!swiping && movingSwipePoint.x - touchBegin.x > SWIPE_DISTANCE) && touchRect.intersectsRect(swipeUpRect)) {
//        swipeUp = true;
//        transfer = true;
//        touchBool = false;
//        CCLOG("1");
//    }
    
    
    
//    else if ((movingSwipePoint.y - touchBegin.y > SWIPE_DISTANCE) && touchRect.intersectsRect(swipeUpRect)) {
//        if(movingSwipePoint.x - touchBegin.x > 3)
//        {
//            swipeRight = true;
//            transfer = true;
//            CCLOG("1");
//        }
//        else if (touchBegin.x - movingSwipePoint.x > 3)
//        {
//            swipeLeft = true;
//            CCLOG("2");
//        }
//        swipeRecognized = true;
//        swipeUp = true;
//        transfer = true;
//
//        CCLOG("3");
//    }
//    else if ((touchBegin.y - movingSwipePoint.y > SWIPE_DISTANCE) && touchRect.intersectsRect(swipeDownRect)) {
//        if(movingSwipePoint.x - touchBegin.x > 0)
//        {
//            swipeRight = true;
//            CCLOG("1");
//        }
//        else if (touchBegin.x - movingSwipePoint.x > 0)
//        {
//            swipeLeft = true;
//            CCLOG("2");
//        }
//        swipeRecognized = true;
//        swipeDown = true;
//        transfer = true;
//        CCLOG("4");
//    }
//    else if (!touchRect.intersectsRect(swipeRightRect) && !touchRect.intersectsRect(swipeLeftRect)
//             && !touchRect.intersectsRect(swipeUpRect) && !touchRect.intersectsRect(swipeDownRect))
//    {
//        swipeRecognized = true;
//        CCLOG("5");
//    }

}

void MyGame::ccTouchesEnded(CCSet* touches, CCEvent* event)
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
        checkRun = true;
    if(transfer){
        checkRun = false;
        transfer =false;
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
    body->CreateFixture(&fixtureDef);
    body->GetFixtureList()->SetSensor(false);
}


void MyGame::runAnimation()
{
    boolAnimaon = false;
    checkRunAnimation = true;
    this->player->throwPlayer(this, ccp(player->getBody()->GetPosition().x * 32, player->getBody()->GetPosition().y * 32));
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
//    ball->createBall(this->world, "bong1.png", ccp(player->getBody()->GetPosition().x, player->getBody()->GetPosition().y + 50));
    ball->createBall(this->world, "bong1.png", ccp(player->getBody()->GetPosition().x *32 , player->getBody()->GetPosition().y * 32 + 30));
    
    this->addChild(ball, 20);
    
    float prercent = timerBar->getPercentage();
    float X = location.x - this->getPosition().x - this->player->getPosition().x * 32;
    float Y = location.y - this->player->getPosition().y * 32;
    float x = prercent/4 * X/(sqrt(X * X + Y * Y));
    float y = prercent/4 * Y/(sqrt(X * X + Y * Y));
    CCLOG("player * %f , ... %f ",player->getPosition().x * 32, player->getPosition().y * 32);
    CCLOG("touches  * %f .. %f ", location.x, location.y);
    b2Vec2 ex = b2Vec2();
    ex.Set(x, y);
    ball->throwBall(ex);
    time = 0;
    arrBalls->addObject(ball);
}
void MyGame::showShooter()
{
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
            world->DestroyBody(ball->getBody());
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
    //this->setPosition(player->getPosition());
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
    CCPoint p = ccp(150 - this->getPosition().x, 120);
    this->removeChild(player);
//    player->setPosition(p);
//    this->addChild(player, 10);
    world->DestroyBody(player->getBody());
    this->player = new Player();
    this->player->createPlayer(this->world, "player.png", p);
    this->addChild(player, 9);

}