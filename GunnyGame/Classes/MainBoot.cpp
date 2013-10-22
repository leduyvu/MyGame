//
//  MainBoot.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/21.
//
//

#include "MainBoot.h"
#include "cocos2d.h"
USING_NS_CC;
MainBoot::MainBoot(){
}
MainBoot::~MainBoot(){
}
void MainBoot::create(string str, CCPoint location, bool life)
{
    this->mainBoot = CCSprite::create(str.c_str());
    this->mainBoot->setPosition(location);
    this->location = 1;

}
void MainBoot::running()
{
    if(this->life)
    {
        if(location == 1)
        {
            this->mainBoot->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(-20,20)),
                                                         CCMoveBy::create(0.5, ccp(-20,-20)),
                                                                          NULL));
            this->location++;
            runLeft = true;
        }
        else if (location == 3){
            this->mainBoot->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(20,20)),
                                                         CCMoveBy::create(0.5, ccp(20,-20)),
                                                         NULL));
            this->location--;
            runLeft = false;
        }
        else if(runLeft){
            this->location++;
            this->mainBoot->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(-20,20)),
                                                         CCMoveBy::create(0.5, ccp(-20,-20)),
                                                         NULL));
        }
        else if (!runLeft)
        {
            this->mainBoot->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(20,20)),
                                                         CCMoveBy::create(0.5, ccp(20,-20)),
                                                         NULL));
            this->location--;
        }
    }
}
CCSprite* MainBoot::getSprite(){
    return this->mainBoot;
}
void MainBoot::setLoction(int location){
    this->location = location;
}
int MainBoot::getLoction(){
    return this->location;
}
void MainBoot::setLife(bool life){
    this->life = life;
}
int MainBoot::getHeart(){
    return this->heart;
}
void MainBoot::setHeart(int heart){
    this->heart = heart;
}
void MainBoot::death(){
    this->mainBoot->runAction(CCMoveBy::create(2, ccp(0, -700)));
}
