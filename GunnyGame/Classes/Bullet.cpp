//
//  Bullet.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/15.
//
//

#include "Bullet.h"
#include "cocos2d.h"
USING_NS_CC;
Bullet::Bullet(){
}
Bullet::~Bullet(){
}
void Bullet::create(b2World * world, string str, CCPoint location, bool turnRight)
{
    bullet = CCSprite::create(str.c_str());
    bullet->setPosition(location);
    this->running();
}
void Bullet::running()
{
    if(turnRight){
        this->bullet->runAction(CCMoveBy::create(10, ccp(3200, 0)));
    }
    else{
        this->bullet->runAction(CCMoveBy::create(10, ccp(-3200, 0)));
    }
}

CCSprite* Bullet::getSprite(){
    return this->bullet;
}
