//
//  Arrow.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/21.
//
//

#include "Arrow.h"
#include "cocos2d.h"
USING_NS_CC;
Arrow::Arrow(){
}
Arrow::~Arrow(){
}
void Arrow::create(string str, CCPoint location, bool life)
{   arrow = CCSprite::create(str.c_str());
    arrow->setPosition(location);
    this->running();
    
}
void Arrow::running()
{
    this->arrow->runAction(CCSequence::create(CCMoveBy::create(2, ccp(0, -500)),
                                              NULL));
}

CCSprite* Arrow::getSprite(){
    return this->arrow;
}
void Arrow::particle(){
    CCParticleExplosion *particle = CCParticleExplosion::create();
    particle->setPosition(this->arrow->getPosition());
    this->arrow->addChild(particle,20);
}