//
//  RoadTransfer.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/09/25.
//
//

#include "RoadTransfer.h"
USING_NS_CC;
RoadTransfer::RoadTransfer()
{
    
}

void RoadTransfer::createBar(CCPoint point)
{
    this->roadBar = CCSprite::create("thanh.png");
    this->roadBar->setPosition(ccp(300,400));
}

void RoadTransfer::swivelBar(int degree)
{
    
}
CCSprite* RoadTransfer::getSprite()
{
    return this->roadBar;
}
RoadTransfer::~RoadTransfer(){}