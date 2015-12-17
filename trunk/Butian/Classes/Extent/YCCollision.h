//
//  STCCollision.h
//  MyCppGame
//
//  Created by siyue on 15/9/16.
//
//

#ifndef __MyCppGame__YCCollision__
#define __MyCppGame__YCCollision__

#include <stdio.h>
#include "Box2D/Box2D.h"
class MainGame;

class ContactListener : public b2ContactListener
{
public:
    MainGame *mainLayer;
private:
    //碰撞开始
    void BeginContact(b2Contact* contact);
    //碰撞结束
    void EndContact(b2Contact* contact);
};


#endif /* defined(__MyCppGame__STCCollision__) */
