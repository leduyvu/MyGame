//
//  File.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/10.
//
//

#include "TopScreen.h"
#include "MainScreen.h"

CCScene* TopScreen::scene()
{
    CCScene *scene = CCScene::create();
    TopScreen *layer = TopScreen::create();
    scene->addChild(layer);
    return scene;
}

bool TopScreen::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    _topScreen = CCSprite::create("poppo_start.png");
    _topScreen->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(_topScreen);
    this->setTouchEnabled(true);
    
    return true;
}

void TopScreen::ccTouchesBegan(CCSet *pTouches, CCEvent *event)
{    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    if (touch) {
        CCDirector::sharedDirector()->replaceScene(MainScreen::scene());
    }
}


