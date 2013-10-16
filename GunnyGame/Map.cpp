//
//  Map.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/07.
//
//

#include "MyGameScene.h"
void MyGame::showShooter()
{
    this->player->setVisible(true);
    time = 0;
    checkRunAnimation = false;
    timerBar->setPercentage(0);
    player->resumeSchedulerAndActions();
    boolAnimaon = false;
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

void  MyGame::setPositionAgian()
{
    this->setTouchEnabled(true);
    CCPoint p = ccp(150 - this->getPosition().x, 120);
    this->removeChild(player);
    //    player->setPosition(p);
    //    this->addChild(player, 10);
    world->DestroyBody(player->getBody());
    this->player = new Player();
    this->player->createPlayer(this->world, "player.png", p);
    this->addChild(player, 9);
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
    bodyDef.position.Set((p.x + (tileSize.width / 1.7f))/pixelsPerMeter,
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
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.0f;
    //    fixtureDef.filter.categoryBits = kFilterCategoryLevel;
    fixtureDef.filter.maskBits = 0xffff;
    body->CreateFixture(&fixtureDef);
    body->SetAngularDamping(1);
    b2Filter filter;
    filter.groupIndex = -2;
    body->GetFixtureList()[0].SetFilterData(filter);
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