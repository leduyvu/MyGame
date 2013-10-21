//
//  MyContactListener.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/09/27.
//
//

#include "MyContactListener.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
MyContactListener::MyContactListener(b2World* world, CCLayer* layer){
    result = false;
    this->world = world;
    this->layer = layer;
    
}
MyContactListener::~MyContactListener(){}
void MyContactListener::BeginContact(b2Contact* contact){
    
}
void MyContactListener::EndContact(b2Contact* contact){
    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    _contacts.push_back(myContact);
    {
       if(myContact.fixtureA->GetDensity() == 0.5)
       {
//          world->DestroyBody(myContact.fixtureA->GetBody());
           //myContact.fixtureA->GetBody()->GetFixtureList()[0].SetSensor(true);
       }
        if(myContact.fixtureB->GetDensity() == 0.5 && myContact.fixtureB->GetBody() != NULL)
        {
           // myContact.fixtureA->GetBody()->GetFixtureList()[0].SetSensor(true);
        }
        
        if (myContact.fixtureA->GetBody()->GetType() == b2_dynamicBody) {
            if (myContact.fixtureB->GetBody()->GetType() == b2_dynamicBody)
            {
                if(myContact.fixtureA->GetDensity() == 900){
                    myContact.fixtureA->GetBody()->SetGravityScale(100);
                    b2Filter filter;
                    filter.groupIndex = 1;
                    myContact.fixtureA->GetBody()->GetFixtureList()[0].SetFilterData(filter);
                }
                if(myContact.fixtureB->GetDensity() == 900)
                {
                    b2Filter filter;
                    filter.groupIndex = 1;
                    myContact.fixtureA->GetBody()->GetFixtureList()[0].SetFilterData(filter);
                    myContact.fixtureB->GetBody()->SetGravityScale(100);
                    
                }
                result = true;
            }
        }
//        if (myContact.fixtureB->GetBody()->GetType() == b2_staticBody || myContact.fixtureA->GetBody()->GetType() == b2_staticBody)
//        {
//            if(myContact.fixtureB->GetDensity() == 0.5)
//                if(myContact.fixtureB->GetBody() != NULL)
//                    //world->DestroyBody(myContact.fixtureB->GetBody());
//            if(myContact.fixtureA->GetDensity() == 0.5)
//                if(myContact.fixtureA->GetBody() != NULL)
//                   // world->DestroyBody(myContact.fixtureA->GetBody());
//            
//            //result = true;
//        }
        
    }
}
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){}
bool MyContactListener::getResult()
{
    return result;
}
void MyContactListener::setResult(bool result)
{
    this->result = result;
}
