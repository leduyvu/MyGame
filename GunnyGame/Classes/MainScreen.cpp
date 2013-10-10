//
//  MainScreen.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/10.
//
//

#include "MainScreen.h"
#include "MyGameScene.h"
USING_NS_CC;
MainScreen::MainScreen(){
    init();
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
    //CCMenuItemLabel *pCloseItem
    CCSize s = CCDirector::sharedDirector()->getWinSize();
//    CCSprite *nen = CCSprite::create("eeee.png");
//    nen->setPosition(ccp(s.width/2, s.height/2));
//    addChild(nen,1);
    CCLabelTTF *play = CCLabelTTF::create("play", "time new roman", 40);
    play->setColor(ccc3(255, 255, 0));
    CCMenuItemLabel *mPlay = CCMenuItemLabel::create(play, this, menu_selector(MainScreen::playGame));
    CCLabelTTF *exit = CCLabelTTF::create("exit", "time new roman", 40);
    exit->setColor(ccc3(255, 255, 0));
    CCMenuItemLabel *mExit = CCMenuItemLabel::create(exit, this, menu_selector(MainScreen::quit));
    
    
    //  CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
    //                                                        "CloseNormal.png",
    //                                                        "CloseSelected.png",
    //                                                        this,
    //                                                       menu_selector(Menu::playGame) );
    mPlay->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 190) );
    mExit->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 150) );
    CCMenu *pMenu = CCMenu::create(mPlay, mExit, NULL);
    // create menu, it's an autorelease object
    //CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);}
MainScreen::~MainScreen(){
}
bool MainScreen::init(){
    return true;
}
CCScene* MainScreen::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // add layer as a child to scene
    CCLayer* layer = new MainScreen();
    scene->addChild(layer);
    layer->release();
    return scene;
}
void MainScreen::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event){
}
void MainScreen::playGame()
{
    CCScene *newScene = MyGame::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,newScene));
}
void MainScreen::quit(){
}