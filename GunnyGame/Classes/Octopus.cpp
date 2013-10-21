//
//  Octupus.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/21.
//
//

#include "Octopus.h"
#include "cocos2d.h"
USING_NS_CC;
Octopus::Octopus(){
}
Octopus::~Octopus(){
}
void Octopus::create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint)
{
    this->octopus = CCSprite::create(str.c_str());
    this->octopus->setPosition(location);
    this->startPoint = startPoint;
    this->endPoint = endPoint;
}
void Octopus::running()
{
    if(this->octopus->getPosition().x <= startPoint.x)
    {
        this->octopus->runAction(CCSequence::create(CCMoveBy::create(1, ccp(150, 50)),
                                                    CCMoveTo::create(1.5, endPoint),
                                                    NULL));
    }
    else if(this->octopus->getPosition().x >= endPoint.x)
    {
        this->octopus->runAction(CCSequence::create(CCMoveBy::create(1, ccp(-150, 50)),
                                                    CCMoveTo::create(1.5, startPoint),
                                                    NULL));
    }
}
CCSprite* Octopus::getSprite(){
    return this->octopus;
}