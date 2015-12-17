//
//  YCEnemySprite.cpp
//  Butian
//
//  Created by apple on 15/12/6.
//
//

#include "YCEnemySprite.hpp"
#include "../Extent/Macros.h"

USING_NS_CC;

EnemySprite* EnemySprite::create(const char *imgName) {
    EnemySprite *sprite = new EnemySprite();
    sprite->imgName = imgName;
    sprite->initSprite();
    return sprite;
}

bool EnemySprite::initSprite() {
    if ( !Sprite::init() )
    {
        return false;
    }
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(this->imgName);
    this->setSpriteFrame(frame);
    this->setName(ENEMY_SPRITE_MACRO);
    
    return true;
}