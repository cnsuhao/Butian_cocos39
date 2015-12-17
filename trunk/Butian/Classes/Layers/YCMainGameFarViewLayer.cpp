//
//  YCMainGameFarViewLayer.cpp
//  Butian
//
//  Created by apple on 15/12/8.
//
//

#include "YCMainGameFarViewLayer.hpp"
#include "../Extent/Macros.h"

bool MainGameFarView::init() {
    if (!Layer::init()) {
        return false;
    }
    
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();
    
    //背景
    Sprite *bgSprite = Sprite::create("chapter1.png");
    float scaleX = 1.2*visibleSize.width/bgSprite->getContentSize().width;
    //float scaleY = 2*visibleSize.height/bgSprite->getContentSize().height;
    bgSprite->setScale(scaleX);
    bgSprite->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    this->addChild(bgSprite,-1);
    
    return true;
}

void MainGameFarView::adjustFarView(Point point,Size mapSize) {
    float adjustX = (visibleSize.width/2-point.x)*FAR_VIEW_RATIO;
    float adjustY = (visibleSize.height/2-point.y)*FAR_VIEW_RATIO;
    
    if (adjustX>0) {
        adjustX = 0;
    }
    if (adjustY>0) {
        adjustY = 0;
    }
    if (-adjustX>(mapSize.width-visibleSize.width)*FAR_VIEW_RATIO) {
        adjustX = (visibleSize.width-mapSize.width)*FAR_VIEW_RATIO;
    }
    if (-adjustY>(mapSize.height-visibleSize.height)*FAR_VIEW_RATIO) {
        adjustY = (visibleSize.height-mapSize.height)*FAR_VIEW_RATIO;
    }

    this->setPosition(Point(adjustX,adjustY));
}

