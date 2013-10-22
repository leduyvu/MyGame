//
//  Laze.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/17.
//
//

#include "Laze.h"
#include "cocos2d.h"
USING_NS_CC;
Laze::Laze(){
}
Laze::~Laze(){
}
void Laze::create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint)
{
    laze = CCSprite::create(str.c_str());
    laze->setPosition(location);
    this->startPoint = startPoint;
    this->endPoint = endPoint;
}
void Laze::running()
{
    
}
CCSprite* Laze::getSprite(){
    return this->laze;
}
