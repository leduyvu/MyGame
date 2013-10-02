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
    this->location = location;
    sprPlayer->setPosition(location);
    
    
    
//    sprPlayer = CCSprite::create("bong1.png");
//    sprPlayer->setPosition(location);
//    sprPhysicPlayer = new PhysicsSprite();
//    this->sprPhysicPlayer->initWithTexture(sprPlayer->getTexture());
//    this->location = location;
//    sprPhysicPlayer->setPosition(location);
//    b2BodyDef bodyDef1;
//    bodyDef1.type = b2_dynamicBody;
//    bodyDef1.position.Set(location.x/32, location.y/32);
//    this->body = world->CreateBody(&bodyDef1);
//    b2CircleShape dynamicBox;
//    dynamicBox.m_radius = 3.3f;
//    b2FixtureDef fixtureDef1;
//    fixtureDef1.shape = &dynamicBox;
//    fixtureDef1.density = 1.0f;
//    fixtureDef1.friction = 0.3f;
//    this->body->CreateFixture(&fixtureDef1);
//    sprPhysicPlayer->setPhysicsBody(body);
}
void Player::movingPlayer(CCPoint point){
    this->sprPlayer->runAction(CCMoveBy::create(1, point));
}

CCSprite* Player::getSprite(){
    return this->sprPlayer;
}
CCPoint Player::getLocation(){
    this->location = sprPlayer->getPosition();
    return this->location;
}
void Player::throwPlayer(CCLayer* layer, CCPoint location){
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
    popSprite->setPosition(location);
    animation->setLoops(1);
    layer->addChild(popSprite, 8);
    popSprite->runAction(CCSequence::create(CCAnimate::create(animation),
                                            CCRemoveSelf::create(),
                                            NULL));
}