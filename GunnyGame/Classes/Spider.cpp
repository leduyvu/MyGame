//
//  Spider.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/10.
//
//

#include "Spider.h"
#include "cocos2d.h"
USING_NS_CC;
Spider::Spider(){
}
Spider::~Spider(){
}
void Spider::create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint)
{
    spider = CCSprite::create(str.c_str());
    spider->setPosition(location);
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    //spider->setScale(0.2);
//    this->initWithTexture(spider->getTexture());
//    this->setScale(0.2);
//    this->setPosition(location);
//    b2BodyDef bodyDef1;
//    bodyDef1.type = b2_dynamicBody;
//    bodyDef1.position.Set(location.x/32, location.y/32);
//    b2Body* body = world->CreateBody(&bodyDef1);
//    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(spider->getContentSize().width/3.5/64, spider->getContentSize().height/64);
//    b2FixtureDef fixtureDef1;
//    fixtureDef1.shape = &dynamicBox;
//    fixtureDef1.density = 1.0f;
//    fixtureDef1.friction = 0;
//    fixtureDef1.restitution = 0;
//    body->CreateFixture(&fixtureDef1);
//    this->setPhysicsBody(body);
}
void Spider::running()
{
    if(spider->getPosition().x < startPoint.x)
    {
//        spider->setPosition(startPoint);
//        spider->runAction(CCMoveTo::create(3, endPoint));
        spider->runAction(CCMoveBy::create(1, ccp(90, 0)));

        checkrunning =false;
    }
    else
    if(spider->getPosition().x <= endPoint.x && spider->getPosition().x >= startPoint.x && !checkrunning)
    {
//        spider->runAction(CCMoveTo::create((endPoint.x - spider->getPosition().x)/2000, endPoint));
        spider->runAction(CCMoveBy::create(1, ccp(90, 0)));

    }
    else
    if(spider->getPosition().x <= endPoint.x && spider->getPosition().x >= startPoint.x && checkrunning)
    {
//        spider->runAction(CCMoveTo::create((spider->getPosition().x - startPoint.x)/2000, startPoint));
        spider->runAction(CCMoveBy::create(1, ccp(-90, 0)));

    }
    else
    if(spider->getPosition().x > endPoint.x)
    {
//        spider->setPosition(endPoint);
//        spider->runAction(CCMoveTo::create(3, startPoint));
        spider->runAction(CCMoveBy::create(1, ccp(-90, 0)));
        checkrunning =true;
    }
}

CCSprite* Spider::getSprite(){
    return this->spider;
}
