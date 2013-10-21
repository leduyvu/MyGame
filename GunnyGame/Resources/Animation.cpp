//
//  Animation.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/15.
//
//

#include "MyGameScene.h"
#include "Turtle.h"
void MyGame::runningSpider()
{
    CCObject *objSpider;
    CCARRAY_FOREACH(this->arrSpider, objSpider){
        Spider* spider = dynamic_cast<Spider*>(objSpider);
        if(spider != NULL)
            spider->running();
    }
    CCObject *obj;
    CCARRAY_FOREACH(this->arrTurtle, obj){
        Turtle* turtle = dynamic_cast<Turtle*>(obj);
        if(turtle != NULL)
            turtle->running();
    }

}

void MyGame::runAnimation()
{
    boolAnimaon = true;
    checkRunAnimation = true;
    this->player->throwPlayer(this, ccp(player->getBody()->GetPosition().x * 32, player->getBody()->GetPosition().y * 32), flipPlayer);
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