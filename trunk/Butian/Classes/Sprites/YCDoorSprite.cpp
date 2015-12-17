//
//  YCDoorSprite.cpp
//  Butian
//
//  Created by apple on 15/12/1.
//
//

#include "YCDoorSprite.hpp"
#include "../Extent/Macros.h"

USING_NS_CC;

DoorSprite* DoorSprite::create(const char *imgName) {
    DoorSprite *sprite = new DoorSprite();
    sprite->imgName = imgName;
    sprite->initSprite();
    return sprite;
}

bool DoorSprite::initSprite() {
    if ( !Sprite::init() )
    {
        return false;
    }
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(this->imgName);
    this->setSpriteFrame(frame);
    cocos2d::Vector<cocos2d::SpriteFrame*>frames;
//    for (int i=0; i<3; i++) {
//        __String *str = __String::createWithFormat("door_%i.png",i);
//        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
//        frames.pushBack(frame);
//    }
//    Animation *animation = Animation::createWithSpriteFrames(frames,1.0f/2.0f);
//    Animate *animate = Animate::create(animation);
    
    //this->runAction(RepeatForever::create(animate));
    
    this->setName(DOOR_SPRITE_MACRO);
    
    return true;
}