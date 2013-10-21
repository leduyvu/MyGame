//
//  Ball.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/09/30.
//
//

#include "Ball.h"
#include "cocos2d.h"
USING_NS_CC;
Ball::Ball(){
}
Ball::~Ball(){
}
void Ball::createBall(b2World * world, string str, CCPoint location)
{
    sprBall = CCSprite::create("bong1.png");
    sprBall->setPosition(location);
    this->initWithTexture(sprBall->getTexture());
    this->setPosition(location);
    b2BodyDef bodyDef1;
    bodyDef1.type = b2_dynamicBody;
    bodyDef1.position.Set(location.x/32, location.y/32);
    b2Body* body = world->CreateBody(&bodyDef1);
    b2CircleShape dynamicBox;
    dynamicBox.m_radius = 0.3f;
    b2FixtureDef fixtureDef1;
    fixtureDef1.shape = &dynamicBox;
    fixtureDef1.density = 0.5f;
    fixtureDef1.friction = 0.0f;
    fixtureDef1.restitution = 1;
    body->CreateFixture(&fixtureDef1);
    b2Filter filter;
    filter.groupIndex = -3;
    body->GetFixtureList()[0].SetFilterData(filter);
    body->SetLinearDamping(0.01);
    this->setPhysicsBody(body);
}
void Ball::throwBall(b2Vec2 vectorV){
    this->getBody()->SetLinearVelocity(vectorV);
}

CCSprite* Ball::getSprite(){
    return this->sprBall;
}
