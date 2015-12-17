//
//  STCCollision.cpp
//  MyCppGame
//
//  Created by siyue on 15/9/16.
//
//

#include "YCCollision.h"
#include "cocos2d.h"
#include "../MainGame/YCMainGameScene.hpp"
USING_NS_CC;

void ContactListener::BeginContact(b2Contact *contact) {
    if (mainLayer!=NULL) {
        mainLayer->beginContactFun(contact);
    }
}

void ContactListener::EndContact(b2Contact *contact) {

}
