//
//  YCWelcomeBGScene.cpp
//  Butian
//
//  Created by apple on 15/12/6.
//
//

#include "YCWelcomeBGScene.hpp"

Scene* WelcomeBG::createScene()
{
    auto scene = Scene::create();
    auto layer = WelcomeBG::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool WelcomeBG::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    Sprite *bg = Sprite::create("bg.jpg");
    bg->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    float scaleX = visibleSize.width/bg->getContentSize().width;
    float scaleY = visibleSize.height/bg->getContentSize().height;
    bg->setScale(scaleX, scaleY);
    this->addChild(bg);
    
    return true;
}
