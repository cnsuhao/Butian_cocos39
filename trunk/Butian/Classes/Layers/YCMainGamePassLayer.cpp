//
//  YCMainGamePassLayer.cpp
//  Butian
//
//  Created by apple on 15/12/3.
//
//

#include "YCMainGamePassLayer.hpp"

bool MainGamePass::init() {
    if (!Layer::init()) {
        return false;
    }
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();
    
    //过关背景
    Sprite *bgSprite = Sprite::create("pass.jpg");
    bgSprite->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    this->addChild(bgSprite,-1);
    
    return true;
}
