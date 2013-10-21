//
//  ImpactHandler.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/15.
//
//

#include "MyGameScene.h"
void MyGame::impactBall(){
    CCObject *obj;
    CCARRAY_FOREACH(this->arrBalls, obj)
    {
        Ball* ball = dynamic_cast<Ball*>(obj);
        if(ball->getBody()->GetPosition().y *32 < 90)
        {
            arrBalls->removeObject(ball);
            this->removeChild(ball);
            ball->autorelease();
            world->DestroyBody(ball->getBody());
        }
        MyContactListener* listenImpact = dynamic_cast<MyContactListener*>(listener);
        if(listenImpact->getResult())
        {
//            listenImpact->setResult(false);
//            if(arrPointDeath->count() > 0){
//                arrPointDeath->removeObjectAtIndex(0);
//            }
//            world->DestroyBody(ball->getBody());
//            arrBalls->removeAllObjects();
//            //this->removeChild(ball);
//            Spider* spider = new Spider();
//            spider->create(this->world, "connhen.png",
//                           ccp(this->getPosition().x + 50, this->getPosition().y + 70),
//                           ccp(200,200),
//                           ccp(500, 200));
//            this->addChild(spider->getSprite(), 10);
//            arrSpider->addObject(spider);
        }
    }
}

void MyGame::impactBoot(){
    CCObject *objSprider, *objTurtle, *objBullet;
    if(player->getHeart() < 100)
    {
        //this->setTouchEnabled(false);
        //this->world->DestroyBody(player->getBody());
        b2Filter filter;
        filter.groupIndex = -2;
        player->getBody()->GetFixtureList()[0].SetFilterData(filter);
        player->getBody()->GetFixtureList()[0].SetSensor(true);
    }
    CCARRAY_FOREACH(this->arrSpider, objSprider){
        Spider* sprider = dynamic_cast<Spider*>(objSprider);
        if(fabs(sprider->getSprite()->getPosition().x - player->getBody()->GetPosition().x * 32) < 10 && fabs(sprider->getSprite()->getPosition().y - player->getBody()->GetPosition().y * 32) < 50){
            this->player->setHeart(this->player->getHeart() - 20);
        }
    }
    CCARRAY_FOREACH(this->arrTurtle, objTurtle){
        Turtle* turtle = dynamic_cast<Turtle*>(objTurtle);
        if(fabs(turtle->getSprite()->getPosition().x - player->getBody()->GetPosition().x * 32) < 10 && fabs(turtle->getSprite()->getPosition().y - player->getBody()->GetPosition().y * 32) < 50){
            this->player->setHeart(this->player->getHeart() - 20);
        }
        
        CCObject* objBall;
        if(arrBalls->count() > 0){
            CCARRAY_FOREACH(arrBalls, objBall){
                Ball* ball = dynamic_cast<Ball*>(objBall);
                if(ball != NULL && fabs(ball->getBody()->GetPosition().x * 32 - turtle->getSprite()->getPosition().x) < 50 && fabs(ball->getBody()->GetPosition().y * 32 - turtle->getSprite()->getPosition().y) < 50){
                    turtle->getSprite()->runAction(CCMoveBy::create(2, ccp(0, -300)));
                }
                
            }
        }
        if(turtle->getSprite()->getPosition().y <= -100){
            this->removeChild(turtle->getSprite());
            arrTurtle->removeObject(turtle);
            turtle->autorelease();
        }
    }
    CCARRAY_FOREACH(this->arrBullet, objBullet){
        Bullet* bullet = dynamic_cast<Bullet*>(objBullet);
        if(fabs(bullet->getSprite()->getPosition().x - player->getBody()->GetPosition().x * 32) < 10 && fabs(bullet->getSprite()->getPosition().y - player->getBody()->GetPosition().y * 32) < 50 && bullet->getShoot()){
            this->player->setHeart(this->player->getHeart() - 20);
            bullet->setShoot(false);
        }
//        if(bullet->getSprite()->getPosition().x < this->getPosition().x * (-1) || bullet->getSprite()->getPosition().x < this->getPosition().x * (-1) + 1200){
//            this->removeChild(bullet->getSprite());
//            arrBullet->removeObject(bullet);
//            bullet->autorelease();
//        }
    }
    CCObject* objectOctopus;
    CCARRAY_FOREACH(this->arrOctopus, objectOctopus){
        Octopus* octopus = dynamic_cast<Octopus*>(objectOctopus);
        if(fabs(octopus->getSprite()->getPosition().x - player->getBody()->GetPosition().x * 32) < 30 && fabs(octopus->getSprite()->getPosition().y - player->getBody()->GetPosition().y * 32) < 30){
            this->player->setHeart(this->player->getHeart() - 20);
        }
    }
}