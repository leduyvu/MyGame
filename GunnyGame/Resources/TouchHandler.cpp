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
    checkRun = false;
    CCSetIterator it;
    CCTouch *touch = (CCTouch*)touches->anyObject();
    this->touchBegin = this->getParent()->convertTouchToNodeSpace(touch);
    touchBool = true;
    
    if(player->getBody()->GetPosition().x *32 >= 5630){
        CCRect touchRect = CCRect(touchBegin.x - this->getPosition().x, touchBegin.y - this->getPosition().y, 40, 40);
        CCRect shootRect = CCRectMake(shootButton->getPosition().x, shootButton->getPosition().y, shootButton->getContentSize().width, shootButton->getContentSize().height);
        if (touchRect.intersectsRect(shootRect))
        {
            CCObject* objBall;
            CCARRAY_FOREACH(arrBalls, objBall){
                Ball* ball = dynamic_cast<Ball*>(objBall);
                Arrow* arrow = new Arrow();
                arrow->create("ten.png", ccp(ball->getBody()->GetPosition().x * 32, ball->getBody()->GetPosition().y * 32), true);
                this->addChild(arrow->getSprite(), 12);
                arrBalls->removeObject(ball);
                this->removeChild(ball);
                this->arrArrow->addObject(arrow);
                ball->autorelease();
                world->DestroyBody(ball->getBody());
                touchBegin = ccp(player->getBody()->GetPosition().x *32,1000000);
                touchBool = false;
                transfer =true;
                //return;
            }
        }
    }
    
    if(player->getBody()->GetPosition().x * 32 - flipPlayer && touchBegin.x + this->getPosition().x > 50 )
    {
        player->setFlipX(false);
        flipPlayer = false;
    }
    if(!flipPlayer && touchBegin.x - this->getPosition().x - player->getBody()->GetPosition().x * 32 > 50)
    {
        player->setFlipX(true);
        flipPlayer = true;
    }
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
            transfer =true;
            time = 0;
            firstMovingUp = true;
            return;
        }
        if ((touchRect.intersectsRect(swipeUpRect))){
            b2Vec2 ex = b2Vec2();
            ex.Set(-2, 12);
            player->movingPlayer(ex);
            touchBool = false;
            transfer =true;
            time = 0;
            firstMovingUp = true;
            return;
        }
        if ((touchRect.intersectsRect(swipeUpRightRect))){
            b2Vec2 ex = b2Vec2();
            ex.Set(2, 12);
            player->movingPlayer(ex);
            touchBool = false;
            transfer =true;
            time = 0;
            firstMovingUp = true;

            return;
        }
        //firstMovingUp = true;
    }

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
    
//    CCRect touchRect = CCRect(location.x - this->getPosition().x, location.y - this->getPosition().y, 30, 30);
//    CCRect shootRect = CCRectMake(shootButton->getPosition().x, shootButton->getPosition().y, shootButton->getContentSize().width, shootButton->getContentSize().height);
//    if (touchRect.intersectsRect(shootRect))
//        return;
    
    
    if(flipPlayer && location.x - this->getPosition().x < player->getBody()->GetPosition().x * 32)
    {
        player->setFlipX(false);
        flipPlayer = false;
    }
    if(!flipPlayer && location.x - this->getPosition().x > player->getBody()->GetPosition().x * 32)
    {
        player->setFlipX(true);
        flipPlayer = true;
    }

    
}
