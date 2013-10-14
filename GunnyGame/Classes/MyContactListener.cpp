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
MyContactListener::MyContactListener(){
    result = false;
}
MyContactListener::~MyContactListener(){}
void MyContactListener::BeginContact(b2Contact* contact){
    
}
void MyContactListener::EndContact(b2Contact* contact){
    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
    _contacts.push_back(myContact);
    {
        if (myContact.fixtureA->GetBody()->GetType() == b2_dynamicBody) {
            if (myContact.fixtureB->GetBody()->GetType() == b2_dynamicBody)
            {
                if(myContact.fixtureA->GetBody()->GetAngularDamping() != 10)
                    myContact.fixtureA->GetBody()->SetGravityScale(100);
                if(myContact.fixtureB->GetBody()->GetAngularDamping() != 10)
                    myContact.fixtureB->GetBody()->SetGravityScale(100);
                result = true;
            }
        }
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
