//
//  YCHeroSprite.cpp
//  Butian
//
//  Created by apple on 15/11/22.
//
//

#include "YCHeroSprite.hpp"
#include "../Extent/Macros.h"

USING_NS_CC;

HeroSprite* HeroSprite::create() {
    HeroSprite *sprite = new HeroSprite();
    sprite->initSprite();
    return sprite;
}

bool HeroSprite::initSprite() {
    if ( !Sprite::init() )
    {
        return false;
    }
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_0.png");
    this->setName(HERO_SPRITE_MACRO);
    this->setSpriteFrame(frame);
    
    return true;
}