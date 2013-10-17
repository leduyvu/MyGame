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
    this->turnRight = turnRight;
    this->running();
    
}
void Bullet::running()
{
    if(this->turnRight){
        this->bullet->runAction(CCMoveBy::create(60, ccp(10200, 0)));
    }
    else{
        this->bullet->runAction(CCMoveBy::create(60, ccp(-10200, 0)));
    }
}

CCSprite* Bullet::getSprite(){
    return this->bullet;
}

bool Bullet::getShoot(){
    return this->shoot;
}
void Bullet::setShoot(bool shoot){
    this->shoot = shoot;
}
