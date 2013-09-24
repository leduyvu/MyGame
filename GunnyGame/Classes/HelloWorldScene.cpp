//
//  HelloWorldScene.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/09/19.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "math.h"
using namespace cocos2d;
using namespace CocosDenshion;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
};

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_sTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_sTransform;
}

HelloWorld::HelloWorld()
{
    // init physics
    this->initPhysics();
    //==================map=============
    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("mapGunny2.tmx");
    _background = _tileMap->layerNamed("mapWall");
    
    // create all the rectangular fixtures for each tile in the level
    CCSize layerSize = _background->getLayerSize();
    for( int y=0; y < layerSize.height; y++ )
    {
        for( int x=0; x < layerSize.width; x++ )
        {
            // create a fixture if this tile has a sprite
            CCSprite* tileSprite = _background->tileAt(ccp(x, y));
            if( tileSprite )
                this->createRectangularFixture(_background, x, y, 1.0f, 1.0f);
        }
    }
    
    this->addChild(_tileMap);
    //=====================
    
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
//====================add Player =================
    addShooter();
//================================================

//========== Shoot power =========================
    CCSprite *timer = CCSprite::create("bt_progressbar1.png");
    timer->setAnchorPoint(ccp(0, 0));
    timerBar = CCProgressTimer::create(timer);
    
    timerBar->setType(kCCProgressTimerTypeBar);
    timerBar->setAnchorPoint(ccp(0, 0));
    
    timerBar->setPosition(100, 100);
    timerBar->setMidpoint(ccp(0, 0));
    timerBar->setBarChangeRate(ccp(1, 0));
    
    timerBar->setTag(405);
    this->addChild(timerBar, 10);
    timerBar->setPercentage(0);
//=================================================
    
//======================= BALL =========================
    CCSpriteBatchNode *sprBoom = CCSpriteBatchNode::create("bong1.png", 100);
    //sprBoom->setScale(0.3);
    textture = sprBoom->getTexture();
    addChild(sprBoom, 0, 222);
    
    CCSprite* ro = CCSprite::create("robong.png");
    ro->setPosition(ccp(200,455));
    ro->setScale(3);
    ro->setFlipX(true);
    this->addChild(ro,4);
    
    CCSize tileSize = this->_tileMap->getTileSize();
    const float pixelsPerMeter = 32.0f;
    
    // create the body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(200/pixelsPerMeter,
                         (200/ 2.0f)/pixelsPerMeter);
    b2Body *body = world->CreateBody(&bodyDef);
    
    // define the shape
    b2PolygonShape shape;
    shape.SetAsBox(60 / pixelsPerMeter,
                   60/ pixelsPerMeter);
    
    // create the fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.0f;
    //    fixtureDef.filter.categoryBits = kFilterCategoryLevel;
    fixtureDef.filter.maskBits = 0xffff;
    body->CreateFixture(&fixtureDef);
    
//========================================================

    scheduleUpdate();
    this->schedule(schedule_selector(HelloWorld::runBoot), 2.55);
}

HelloWorld::~HelloWorld()
{
    delete world;
    world = NULL;
}

void HelloWorld::initPhysics()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
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
    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);

//    // top
//    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
//    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
}

void HelloWorld::addShooter()
{
    sprite = CCSprite::create("nembong1.png");
    sprite->setScale(0.3);
    this->addChild(sprite);
    sprite->setPosition(ccp(800, 150));
    
}

void HelloWorld::draw()
{
    CCLayer::draw();
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    world->DrawDebugData();
    kmGLPopMatrix();
}

void HelloWorld::addNewSpriteAtPosition(CCPoint p){}

void HelloWorld::update(float dt)
{
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
        this->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(HelloWorld::runAnimation)),
                                           CCDelayTime::create(1.6),
                                           CCCallFunc::create(this, callfunc_selector(HelloWorld::throwBall)),
                                           CCCallFunc::create(this, callfunc_selector(HelloWorld::showShooter)),
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
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }    
    }
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
//    timerBar->setPercentage(0);
    time = 0;
    CCSetIterator it;
    CCTouch* touch;
    it = touches->begin();
    touch = (CCTouch*)(*it);
    touchBegin = touch->getLocationInView();
//    touchBegin = CCDirector::sharedDirector()->convertToGL(location);
//    CCLOG("sprite Location x:: %f",sprite->getPosition().x);
    CCLOG("touchBegin Location x:: %f",touchBegin.x);
//    CCLOG("sprite Location y:: %f",sprite->getPosition().y);
    CCLOG("touchBegin Location y:: %f",s.height - touchBegin.y);

    if(fabs(touchBegin.x - sprite->getPosition().x) < 100 && fabs(s.height - touchBegin.y - sprite->getPosition().y) < 100)
    {
        transfer = true;
        touchBool = false;
    }
    else  if(!checkRunAnimation) touchBool = true;
    
}

void HelloWorld::ccTouchesMoved (CCSet *touches, CCEvent *event) {
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    if(transfer)
    {
        if(touchLoc.x > touchBegin.x && touchBegin.x > 0)
        {
            sprite->runAction(CCMoveBy::create(1, ccp(90,0)));
            transfer = false;
            touchBegin = ccp(0,0);

        }
        else if(touchLoc.x < touchBegin.x && touchBegin.x > 0)
        {
            sprite->runAction(CCMoveBy::create(1, ccp(-90,0)));
            transfer = false;
            touchBegin = ccp(0,0);
        }
    }
    
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
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

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

void HelloWorld::createRectangularFixture(CCTMXLayer* layer, int x, int y,
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

void HelloWorld::runAnimation()
{
    checkRunAnimation = true;
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("nembong.plist");
    CCArray* animFrames = new CCArray;
    animFrames->autorelease();
    char str[100] = {0};
    for(int i = 1; i < 6; i++) {
        sprintf(str, "nembong%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3);
    CCSprite *popSprite = CCSprite::create();
    popSprite->setScale(0.3);
    popSprite->setPosition(sprite->getPosition());
    sprite->setVisible(false);
    animation->setLoops(1);
    this->addChild(popSprite, 8);
    popSprite->runAction(CCSequence::create(CCAnimate::create(animation),
                                            CCRemoveSelf::create(),
                                            NULL));

}

void HelloWorld::runBoot()
{
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
    popSprite->setPosition(ccp(150, 150));
    animation->setLoops(1);
    this->addChild(popSprite, 28);
    popSprite->runAction(CCSequence::create(CCAnimate::create(animation),
                                            CCRemoveSelf::create(),
                                            NULL));
    
}


void HelloWorld::throwBall()
{
    float prercent = timerBar->getPercentage();
    CCNode* parent = getChildByTag(222);
    
    //We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    //just randomly picking one of the images

    PhysicsSprite* sprite = new PhysicsSprite();
    sprite->setTag(1120);
    //        sprite->initWithTexture(m_pSpriteTexture, CCRectMake(32 * idx,32 * idy,32,32));
    sprite->initWithTexture(textture);
    sprite->autorelease();
    
    parent->addChild(sprite);
    
    sprite->setPosition(this->sprite->getPosition());

    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(this->sprite->getPosition().x/PTM_RATIO, this->sprite->getPosition().y/PTM_RATIO);
    b2Body *body = world->CreateBody(&bodyDef);
    // Define another box shape for our dynamic body.
    b2CircleShape dynamicBox;
//    dynamicBox.SetAsBox(.4f, .4f);//These are mid points for our 1m box
    dynamicBox.m_radius = 0.3f;
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    sprite->setPhysicsBody(body);
    
    //set velocity
    float X = location.x - this->sprite->getPosition().x;
    float Y = location.y - this->sprite->getPosition().y;
    float x = prercent/4 * X/(sqrt(X * X + Y * Y));
    float y = prercent/4 * Y/(sqrt(X * X + Y * Y));
    b2Vec2 ex = b2Vec2();
    ex.Set(x, y);
    time = 0;
    body->SetLinearVelocity(ex);
    
    
    //restart
    
}
void HelloWorld::showShooter()
{
    sprite->setVisible(true);
    checkRunAnimation = false;
    timerBar->setPercentage(0);
}