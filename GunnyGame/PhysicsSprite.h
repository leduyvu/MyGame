
#ifndef __GunnyGame__PhysicsSprite__
#define __GunnyGame__PhysicsSprite__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"
USING_NS_CC;

class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
    b2Body* getBody();
private:
    b2Body* m_pBody;    // strong ref
};
#endif /* defined(__GunnyGame__PhysicsSprite__) */
