//
//  boot.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/01.
//
//

#include "Boot.h"
#include "PhysicsSprite.h"
#include "MyGameScene.h"
#include "SimpleAudioEngine.h"
#include "PhysicsSprite.h"
#include "math.h"
#include "Player.h"
#include "Ball.h"
Boot::Boot(){
}
Boot::~Boot(){
}
void Boot::createBoot(b2World * world, string str, CCPoint location){
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("quaivat.plist");
    CCArray* animFrames = new CCArray;
    animFrames->autorelease();
    char strc[100] = {0};
    for(int i = 1; i < 6; i++) {
        sprintf(strc, "no%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( strc );
        animFrames->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.4);
    CCSprite *popSprite = CCSprite::create();
    //popSprite->setScale();
    animation->setLoops(7);
    animation->setLoops(1);
    this->addChild(popSprite, 28);
    popSprite->runAction(CCSequence::create(CCAnimate::create(animation),
                                            CCRemoveSelf::create(),
                                            NULL));

}
