//
//  YCMainGameFarViewLayer.hpp
//  Butian
//
//  Created by apple on 15/12/8.
//
//

#ifndef YCMainGameFarViewLayer_hpp
#define YCMainGameFarViewLayer_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;

class MainGameFarView:public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(MainGameFarView);
    void adjustFarView(Point point,Size mapSize);
private:
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
};

#endif /* YCMainGameFarViewLayer_hpp */
