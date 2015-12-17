//
//  YCWelcomeBGScene.hpp
//  Butian
//
//  Created by apple on 15/12/6.
//
//

#ifndef YCWelcomeBGScene_hpp
#define YCWelcomeBGScene_hpp

#include "cocos2d.h"

USING_NS_CC;

class WelcomeBG : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(WelcomeBG);
private:
    Size visibleSize;
    Vec2 origin;
};

#endif /* YCWelcomeBGScene_hpp */
