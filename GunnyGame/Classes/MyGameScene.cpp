//
//  MyGameScene.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/09/19.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "PhysicsSprite.h"
#include "MyGameScene.h"
#include "Turtle.h"
USING_NS_CC;
MyGame::MyGame()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
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
    
    PointDeath * pd4 = new PointDeath();
    pd4->create(ccp(4530, 120), ccp(4810,120));
    arrPointDeath->addObject(pd4);
    
    PointDeath * pd5 = new PointDeath();
    pd5->create(ccp(5250, 120), ccp(5470,120));
    arrPointDeath->addObject(pd5);
    
//    PointDeath * pd6 = new PointDeath();
//    pd6->create(ccp(6180, 120), ccp(6350,120));
//    arrPointDeath->addObject(pd6);
//================================================
//====================add Player =================
    this->player->createPlayer(this->world, "player.png", ccp(6100, 120));
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
    
//============heartBar===========================
    CCSprite *hearts = CCSprite::create("heart.png");
    hearts->setAnchorPoint(ccp(0, 0));
    hearts->setScale(4);
    heartBar = CCProgressTimer::create(timer);
    heartBar->setType(kCCProgressTimerTypeBar);
    heartBar->setAnchorPoint(ccp(0, 0));
    heartBar->setPosition(ccp(0, s.height/1.3));
    heartBar->setMidpoint(ccp(0,0));
    heartBar->setBarChangeRate(ccp(1, 0));
    this->addChild(heartBar, 10);
    heartBar->setPercentage(100);
//==============================================
    
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
    Turtle * turtle = new Turtle();
    turtle->create(this->world, "rua2.png", ccp(2400,170), ccp(2100,170), ccp(800,2470));
    arrTurtle->addObject(turtle);
    Turtle * turtle2 = new Turtle();
    turtle2->create(this->world, "rua2.png", ccp(600,190), ccp(800,190), ccp(500,190));
    arrTurtle->addObject(turtle2);
    this->addChild(turtle->getSprite(), 10);
    this->addChild(turtle2->getSprite(), 10);
    
    CCSprite* gun = CCSprite::create("gun.png");
    gun->setTag(1122);
    gun->setPosition(ccp(1400, 100));
    CCSprite* gun2 = CCSprite::create("gun.png");
    gun2->setTag(1122);
    gun2->setPosition(ccp(4100, 250));
    arrGun->addObject(gun2);
    this->addChild(gun2);
    
//====================== Octopus ==============
    Octopus *ocp =new Octopus();
    ocp->create(this->world, "octopus.png", ccp(3900, 140), ccp(3900, 140), ccp(4100, 120));
    this->addChild(ocp->getSprite(), 10);
    arrOctopus->addObject(ocp);
    
    Octopus *ocp1 =new Octopus();
    ocp1->create(this->world, "octopus.png", ccp(4650, 140), ccp(4500, 120), ccp(4650, 120));
    this->addChild(ocp1->getSprite(), 10);
    arrOctopus->addObject(ocp1);
    
    Octopus *ocp2 =new Octopus();
    ocp2->create(this->world, "octopus.png", ccp(5020, 140), ccp(5020, 140), ccp(5150, 120));
    this->addChild(ocp2->getSprite(), 10);
    arrOctopus->addObject(ocp2);

    //===================================
    //================= spider===================
    Spider* spider = new Spider();
    spider->create(this->world,
                   "connhen.png",
                   ccp(this->getPosition().x + 1700, this->getPosition().y + 80),
                   ccp(1500, 80),
                   ccp(1700, 80));
    this->addChild(spider->getSprite(), 10);
    arrSpider->addObject(spider);

    
    //===========================================
    
    
    
//    CCParticleGalaxy* pr = CCParticleGalaxy::create();
//    pr->setPosition(ccp(700, 120));
//    _tileMap->addChild(pr, 12);
    
    
    
    //chim
    mainboot = new MainBoot();
    mainboot->create("chim1.png", ccp(6250,120), true);
    this->addChild(mainboot->getSprite(),19);
    //shootRect
    shootButton = CCSprite::create("eges.png");
    shootButton->setScale(3);
    shootButton->setPosition(this->getPosition());
    this->addChild(shootButton, 11);
    scheduleUpdate();
    //this->schedule(schedule_selector(MyGame::runBoot), 2.55);
    this->schedule(schedule_selector(MyGame::impactBall));
    this->schedule(schedule_selector(MyGame::runningSpider), 1);
    this->schedule(schedule_selector(MyGame::impactBoot));
    this->schedule(schedule_selector(MyGame::gunShoot), 4);
    
}

MyGame::~MyGame()
{
    delete world;
    world = NULL;
}
bool MyGame::init(){
    this->map = new CCLayer();
    touchBegin = ccp(0, 10000);
    this->arrArrow = new CCArray();
    this->arrMainBullet = new CCArray();
    this->arrOctopus = new CCArray();
    this->arrBullet = new CCArray();
    this->arrGun = new CCArray();
    this->arrTurtle = new CCArray();
    this->arrPointDeath = new CCArray();
    this->arrSpider = new CCArray();
    this->arrWall = new CCArray();
    this->arrBalls = new CCArray();
    
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
    listener = new MyContactListener(this->world, this);
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
    CCLOG("player * %f , ... %f ",player->getBody()->GetPosition().x * 32, player->getBody()->GetPosition().y * 32);
    MyGame::handlerPlayer();
        
    if(fabs(player->getBody()->GetLinearVelocity().x) <= 0.01 && fabs(player->getBody()->GetLinearVelocity().y) <= 0.01)
    {
        animationCreate = true;
        
    }
    else animationCreate = false;
    
    if(fabs(player->getBody()->GetLinearVelocity().y) <= 0.01){
        movingUp = false;
        firstMovingUp = true;
    }
    else{
        movingUp = true;
    }
    //if(player->getBody()->GetPosition().x * 32 <= 5630)
    setViewPointCenter(ccp(player->getBody()->GetPosition().x * 32, player->getBody()->GetPosition().y * 32));
    
    //=================== shoot Power=======================
    timerBar->setPosition(ccp(this->getPosition().x * (-1), this->getPosition().y));
    //=====================================================
    //================shootButton==================
    shootButton->setPosition(ccp(this->getPosition().x * (-1) + 100, this->getPosition().y + 300));
    if(player->getBody()->GetPosition().x *32 >= 5630)
        shootButton->setVisible(true);
    else
        shootButton->setVisible(false);
    //=============================================
    heartBar->setPosition(ccp(this->getPosition().x * (-1), 500));

    //timerBar->getSprite()->setPosition(this->getPosition());

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
    
    if(animationCreate && arrBalls->count() < 1 && timerBar->getPercentage() > 20 && checkRun)
    {
        checkRun =false;
        this->runAction(CCSequence::create(
                                           CCCallFunc::create(this, callfunc_selector(MyGame::relaxMoving)),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::runAnimation)),
                                           CCDelayTime::create(1.2),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::throwBall)),
                                           CCCallFunc::create(this, callfunc_selector(MyGame::showShooter)),
                                           NULL));
    }
    if(boolAnimaon){
        this->setTouchEnabled(false);
    }
    else{
        this->setTouchEnabled(true);
    }
    MyGame::movingVer();
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

void MyGame::throwBall()
{
    if(arrBalls->count() == 0){
        Ball *ball = new Ball();
    //    ball->createBall(this->world, "bong1.png", ccp(player->getBody()->GetPosition().x, player->getBody()->GetPosition().y + 50));
        ball->createBall(this->world, "bong1.png", ccp(player->getBody()->GetPosition().x *32 , player->getBody()->GetPosition().y * 32 + 30));
        ball->setTag(11111);
        this->addChild(ball, 20);
        
        float prercent = timerBar->getPercentage();
        float X = location.x - this->getPosition().x - this->player->getBody()->GetPosition().x * 32;
        float Y = location.y - this->player->getBody()->GetPosition().y * 32;
        float x = prercent/4 * X/(sqrt(X * X + Y * Y));
        float y = prercent/4 * Y/(sqrt(X * X + Y * Y));
        CCLOG("touches  * %f .. %f ", location.x, location.y);
        b2Vec2 ex = b2Vec2();
        ex.Set(x, y);
        ball->throwBall(ex);
        time = 0;
        arrBalls->addObject(ball);
    }
}


void MyGame::mapPosition(CCPoint point){
    //this->setPosition(player->getPosition());
}


void MyGame::relaxMoving(){
    //this->setTouchEnabled(true);
    swipeRight = false;
    swipeLeft = false;
    swipeUp = false;
    swipeDown = false;
    swipeRight = false;
    transfer = false;
    touchBool = false;
    moving = false;
}

void MyGame::gunShoot(){
    //shoot by the gun
    
    
    CCObject* obj;
    CCARRAY_FOREACH(arrGun, obj){
        CCSprite* gun = dynamic_cast<CCSprite*>(obj);
        Bullet* bulletRight = new Bullet();
        bulletRight->create(this->world, "bullet1.png", gun->getPosition(), true);
        Bullet* bulletLeft = new Bullet();
        bulletLeft->create(this->world, "bullet2.png", gun->getPosition(), false);
        this->addChild(bulletRight->getSprite(), 12);
        this->addChild(bulletLeft->getSprite(), 11);
        arrBullet->addObject(bulletRight);
        arrBullet->addObject(bulletLeft);
    }
    // Octopus running
    CCObject* objectOctopus;
    CCLOG("dsdsdsd %d", arrOctopus->count());
    CCARRAY_FOREACH(arrOctopus, objectOctopus){
        Octopus* ocp = dynamic_cast<Octopus*>(objectOctopus);
        ocp->running();
    }
    //MainBoot running
    mainboot->running();
    CCSprite * mainBullet = CCSprite::create("ege.png");
    
    mainBullet->setPosition(ccp(mainboot->getSprite()->getPosition().x - mainboot->getSprite()->getContentSize().width/2, mainboot->getSprite()->getPosition().y + mainboot->getSprite()->getContentSize().width/2));
    this->addChild(mainBullet, 8);
    arrMainBullet->addObject(mainBullet);
    mainBullet->runAction(CCMoveTo::create(3, ccp(player->getBody()->GetPosition().x * 32,player->getBody()->GetPosition().y * 32)));
    
    
}
void MyGame::handlerPlayer(){
    if(heartBar->getPercentage() == 0){
        player->getBody()->GetFixtureList()[0].SetSensor(true);
    }
    if((player->getBody()->GetPosition().x * 32 <= 4150 && player->getBody()->GetPosition().x * 32 >= 3540 && player->getBody()->GetPosition().y * 32 < 300) || (player->getBody()->GetPosition().x * 32 <= 5535 && player->getBody()->GetPosition().x * 32 >= 4150 && player->getBody()->GetPosition().y * 32 < 350))
    {
        heartBar->setPercentage(heartBar->getPercentage() - 0.1);
    }else
        heartBar->setPercentage(100);
    
    if(player->getBody()->GetPosition().y * 32 < -150)
    {
        setPositionAgian();
        heartBar->setPercentage(100);
    }

}
void MyGame::movingVer(){
    if(touchBegin.y <= player->getBody()->GetPosition().y * 32 + 70)
    {
        transfer = true;
        touchBool = false;
        if(!movingUp || (movingUp && firstMovingUp)){
            if (touchBegin.x - this->getPosition().x - player->getBody()->GetPosition().x * 32 > 50)
            {
                b2Vec2 ex = b2Vec2();
                float x = touchBegin.x - this->getPosition().x - player->getBody()->GetPosition().x * 32;
                if(!movingUp)
                    ex.Set(sqrt(0.5 * fabs(x)), 02);
                else if(movingUp && firstMovingUp)
                    ex.Set(4, 0.5);
                ex.Set(5, 1);
                player->movingPlayer(ex);
                firstMovingUp = false;
            }
            if(player->getBody()->GetPosition().x * 32 - (touchBegin.x - this->getPosition().x) > 50){
                b2Vec2 ex = b2Vec2();
                float x = 0;
                if(player->getBody() != NULL)
                    x =  player->getBody()->GetPosition().x * 32 - (touchBegin.x - this->getPosition().x);
                if(!movingUp)
                    ex.Set(sqrt(0.5 * fabs(x)) * (-1), 02);
                else if(movingUp && firstMovingUp)
                    ex.Set(-3, 0.5);
                ex.Set(-5, 1);
                player->movingPlayer(ex);
                firstMovingUp = false;
                
            }
        }
    }
}

