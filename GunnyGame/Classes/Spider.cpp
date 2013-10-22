//
//  Spider.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/10.
//
//

#include "Spider.h"
#include "cocos2d.h"
USING_NS_CC;
Spider::Spider(){
}
Spider::~Spider(){
}
void Spider::create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint)
{
    spider = CCSprite::create(str.c_str());
    spider->setPosition(location);
    this->startPoint = startPoint;
    this->endPoint = endPoint;
}
void Spider::running()
{
    if(spider->getPosition().x < startPoint.x)
    {
//        spider->setPosition(startPoint);
//        spider->runAction(CCMoveTo::create(3, endPoint));
        spider->runAction(CCMoveBy::create(1, ccp(90, 0)));

        checkrunning =false;
    }
    else
    if(spider->getPosition().x <= endPoint.x && spider->getPosition().x >= startPoint.x && !checkrunning)
    {
//        spider->runAction(CCMoveTo::create((endPoint.x - spider->getPosition().x)/2000, endPoint));
        spider->runAction(CCMoveBy::create(1, ccp(90, 0)));

    }
    else
    if(spider->getPosition().x <= endPoint.x && spider->getPosition().x >= startPoint.x && checkrunning)
    {
//        spider->runAction(CCMoveTo::create((spider->getPosition().x - startPoint.x)/2000, startPoint));
        spider->runAction(CCMoveBy::create(1, ccp(-90, 0)));

    }
    else
    if(spider->getPosition().x > endPoint.x)
    {
//        spider->setPosition(endPoint);
//        spider->runAction(CCMoveTo::create(3, startPoint));
        spider->runAction(CCMoveBy::create(1, ccp(-90, 0)));
        checkrunning =true;
    }
}

CCSprite* Spider::getSprite(){
    return this->spider;
}
