#ifndef __GunnyGame__MyContactListener__
#define __GunnyGame__MyContactListener__

#include <iostream>
#include "MyGameScene.h"
#include <Box2D/Box2D.h>
#include <vector>
struct MyContact {
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    bool operator==(const MyContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};
class MyContactListener : public b2ContactListener {
public:
    std::vector<MyContact> _contacts;
    MyContactListener(b2World* world, CCLayer* layer);
    ~MyContactListener();

    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    bool getResult();
    void setResult(bool result);
private:
    CCLayer* layer;
    b2World* world;
    bool result;
    CC_SYNTHESIZE(int, _numberBegin, NumberBegin);
    CC_SYNTHESIZE(int, _numberEnd, NumberEnd);
};
    
#endif /* defined(__AirHockey__MyContactListener__) */