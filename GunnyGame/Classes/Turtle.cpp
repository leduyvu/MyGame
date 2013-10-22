//
//  Turtle.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/15.
//
//

#include "Turtle.h"
#include "cocos2d.h"
USING_NS_CC;
Turtle::Turtle(){
}
Turtle::~Turtle(){
}
void Turtle::create(b2World * world, string str, CCPoint location, CCPoint startPoint, CCPoint endPoint)
{
    turtle = CCSprite::create(str.c_str());
    turtle->setPosition(location);
    turtle->setScale(3);
    this->startPoint = startPoint;
    this->endPoint = endPoint;
}
void Turtle::running()
{
    if(turtle->getPosition().x < startPoint.x)
    {
        turtle->runAction(CCMoveBy::create(1, ccp(90, 0)));
        
        checkrunning =false;
    }
    else
        if(turtle->getPosition().x <= endPoint.x && turtle->getPosition().x >= startPoint.x && !checkrunning)
        {
            turtle->runAction(CCMoveBy::create(1, ccp(90, 0)));
            
        }
        else
            if(turtle->getPosition().x <= endPoint.x && turtle->getPosition().x >= startPoint.x && checkrunning)
            {
                turtle->runAction(CCMoveBy::create(1, ccp(-90, 0)));
                
            }
            else
                if(turtle->getPosition().x > endPoint.x)
                {
                    //        Turtle->setPosition(endPoint);
                    //        Turtle->runAction(CCMoveTo::create(3, startPoint));
                    turtle->runAction(CCMoveBy::create(1, ccp(-90, 0)));
                    checkrunning =true;
                }
}

CCSprite* Turtle::getSprite(){
    return this->turtle;
}
