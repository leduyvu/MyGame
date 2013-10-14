//
//  Player.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/09/30.
//
//

#include "Player.h"
#include "cocos2d.h"
USING_NS_CC;
Player::Player(){
}
Player::~Player(){
}
void Player::createPlayer(b2World * world, string str, CCPoint location)
{
    this->sprPlayer = CCSprite::create(str.c_str());
    this->sprPlayer->setPosition(location);
    this->initWithTexture(sprPlayer->getTexture());
    this->setPosition(location);
    b2BodyDef bodyDef1;
    bodyDef1.type = b2_dynamicBody;
    bodyDef1.position.Set(location.x/32, location.y/32);
    b2Body* body = world->CreateBody(&bodyDef1);
    b2FixtureDef fixtureDef1;
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(sprPlayer->getContentSize().width/64, sprPlayer->getContentSize().height/64);
    fixtureDef1.shape = &dynamicBox;
    fixtureDef1.density = 1.0f;
    fixtureDef1.friction = 1.0f;
    fixtureDef1.restitution = 0;
    body->CreateFixture(&fixtureDef1);
    body->SetFixedRotation(true);
    b2Filter filter;
    filter.groupIndex = -1;
    body->GetFixtureList()[0].SetFilterData(filter);
    body->SetAngularDamping(10);
    this->setPhysicsBody(body);
    this->setFlipX(true);
}
void Player::movingPlayer(b2Vec2 ex){
    this->getBody()->SetLinearVelocity(ex);
}

CCSprite* Player::getSprite(){
    return this->sprPlayer;
}

void Player::setLocation(CCPoint p)
{
    this->sprPlayer->setPosition(p);
}
void Player::throwPlayer(CCLayer* layer, CCPoint location){
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("nembong.plist");
    CCArray* animFrames = new CCArray;
    animFrames->autorelease();
    char str[100] = {0};
    for(int i = 1; i < 6; i++){
        sprintf(str, "nembong%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3);
    CCSprite *popSprite = CCSprite::create();
    popSprite->setScale(0.2);
    popSprite->setFlipX(true);
    popSprite->setPosition(location);
    animation->setLoops(1);
    layer->addChild(popSprite, 18);
    popSprite->runAction(CCSequence::create(CCAnimate::create(animation),
                                            CCRemoveSelf::create(),
                                            NULL));
}