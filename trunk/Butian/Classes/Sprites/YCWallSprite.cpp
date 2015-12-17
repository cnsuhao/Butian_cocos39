//
//  YCWallSprite.cpp
//  Butian
//
//  Created by apple on 15/11/22.
//
//

#include "YCWallSprite.hpp"
#include "../Extent/Macros.h"

USING_NS_CC;

WallSprite* WallSprite::create(const char *imgName) {
    WallSprite *sprite = new WallSprite();
    sprite->imgName = imgName;
    sprite->initSprite();
    return sprite;
}

bool WallSprite::initSprite() {
    if ( !Sprite::init() )
    {
        return false;
    }
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(this->imgName);
    this->setSpriteFrame(frame);
    this->setName(WAll_SPRITE_MACRO);
    
    return true;
}