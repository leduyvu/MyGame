//
//  TouchHandler.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/15.
//
//

#include "MyGameScene.h"
USING_NS_CC;
void MyGame::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    time = 0;
    CCSetIterator it;
    CCTouch *touch = (CCTouch*)touches->anyObject();
    this->touchBegin = this->getParent()->convertTouchToNodeSpace(touch);
    touchBool = true;
  //    if(touchBegin.y <= player->getBody()->GetPosition().y * 32 + 50)
//    {
//        transfer = true;
//        touchBool = false;
//        if(!movingUp || (movingUp && firstMovingUp)){
//            if (touchBegin.x - this->getPosition().x - player->getBody()->GetPosition().x * 32 > 50)
//            {
//                b2Vec2 ex = b2Vec2();
//                float x = touchBegin.x - this->getPosition().x - player->getBody()->GetPosition().x * 32;
//                if(!movingUp)
//                    ex.Set(sqrt(0.5 * fabs(x)), 02);
//                else if(movingUp && firstMovingUp)
//                    ex.Set(3, 0.5);
//                player->movingPlayer(ex);
//                firstMovingUp = false;
//            }
//            if(player->getBody()->GetPosition().x * 32 - (touchBegin.x - this->getPosition().x) > 50){
//                b2Vec2 ex = b2Vec2();
//                float x = 0;
//                if(player->getBody() != NULL)
//                    x =  player->getBody()->GetPosition().x * 32 - (touchBegin.x - this->getPosition().x);
//                if(!movingUp)
//                    ex.Set(sqrt(0.5 * fabs(x)) * (-1), 02);
//                else if(movingUp && firstMovingUp)
//                    ex.Set(-3, 0.5);
//                player->movingPlayer(ex);
//                firstMovingUp = false;
//
//            }
//        }
//    }
}

void MyGame::ccTouchesMoved (CCSet *touches, CCEvent *event) {
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchLoc = this->getParent()->convertTouchToNodeSpace(touch);
    CCRect touchRect = CCRect(touchLoc.x - this->getPosition().x, touchLoc.y - this->getPosition().y, 30, 30);
    CCRect swipeUpRect = CCRectMake(player->getBody()->GetPosition().x * 32 - 20, player->getBody()->GetPosition().y * 32 + 40, 20, 150);
    CCRect swipeUpRightRect = CCRectMake(player->getBody()->GetPosition().x * 32 + 20, player->getBody()->GetPosition().y * 32 + 40, 20, 150);
    if(!movingUp)
    {
        if (touchRect.intersectsRect(swipeUpRect) && touchRect.intersectsRect(swipeUpRightRect)){
            b2Vec2 ex = b2Vec2();
            ex.Set(0, 12);
            player->movingPlayer(ex);
            touchBool = false;
            time = 0;
            firstMovingUp = true;
            return;
        }
        if ((touchRect.intersectsRect(swipeUpRect))){
            b2Vec2 ex = b2Vec2();
            ex.Set(-2, 12);
            player->movingPlayer(ex);
            touchBool = false;
            time = 0;
            firstMovingUp = true;
            return;
        }
        if ((touchRect.intersectsRect(swipeUpRightRect))){
            b2Vec2 ex = b2Vec2();
            ex.Set(2, 12);
            player->movingPlayer(ex);
            touchBool = false;
            time = 0;
            firstMovingUp = true;

            return;
        }
        //firstMovingUp = true;
    }
//    else{
//        if(firstMovingUp)
//        {
//            firstMovingUp = false;
//            if (touchRect.intersectsRect(swipeUpRect) && touchRect.intersectsRect(swipeUpRightRect)){
//                b2Vec2 ex = b2Vec2();
//                ex.Set(0, 3);
//                player->movingPlayer(ex);
//                touchBool = false;
//                time = 0;
//                
//                return;
//            }
//            if ((touchRect.intersectsRect(swipeUpRect))){
//                b2Vec2 ex = b2Vec2();
//                ex.Set(-2, 3);
//                player->movingPlayer(ex);
//                touchBool = false;
//                time = 0;
//                return;
//            }
//            if ((touchRect.intersectsRect(swipeUpRightRect))){
//                b2Vec2 ex = b2Vec2();
//                ex.Set(2, 3);
//                player->movingPlayer(ex);
//                touchBool = false;
//                time = 0;
//                return;
//            }
//        
//        }
//    }
}

void MyGame::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
    }
    checkRun = true;
    if(transfer){
        checkRun = false;
        transfer =false;
    }
    touchBool = false;
    touchBegin.setPoint(0, 10000);
}
