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
    sprBall = new PhysicsSprite();
    this->sprBall->create("bong1.png");
    this->location = location;
    sprBall->setPosition(location);
    b2BodyDef bodyDef1;
    bodyDef1.type = b2_dynamicBody;
    bodyDef1.position.Set(location.x/32, location.y/32);
    body = world->CreateBody(&bodyDef1);
    b2CircleShape dynamicBox;
    dynamicBox.m_radius = 0.3f;
    b2FixtureDef fixtureDef1;
    fixtureDef1.shape = &dynamicBox;
    fixtureDef1.density = 1.0f;
    fixtureDef1.friction = 0.3f;
    body->CreateFixture(&fixtureDef1);
    sprBall->setPhysicsBody(body);

}
void Ball::throwBall(b2Vec2 vectorV){
    this->body->SetLinearVelocity(vectorV);
}

void Ball::setLocation(CCPoint location)
{
    this->location = location;
}

CCSprite* Ball::getSprite(){
    return this->sprBall;
}

CCPoint Ball::getLocation(){
    return this->location;
}

b2Body* Ball::getBody()
{
    return this->body;
}