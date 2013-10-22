//
//  MainScreen.h
//  GunnyGame
//
//  Created by macbook_006 on 13/10/10.
//
//

#ifndef __GunnyGame__MainScreen__
#define __GunnyGame__MainScreen__
#include "cocos2d.h"
#include <iostream>
class MainScreen : public cocos2d::CCLayer {
public:
    MainScreen();
    ~MainScreen();
    void playGame();
    void quit();
    bool init();
    // returns a Scene that contains the MyGame as the only child
    static cocos2d::CCScene* scene();
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
};
#endif /* defined(__GunnyGame__MainScreen__) */
