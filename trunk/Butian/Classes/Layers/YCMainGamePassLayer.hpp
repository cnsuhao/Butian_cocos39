//
//  YCMainGamePassLayer.hpp
//  Butian
//
//  Created by apple on 15/12/3.
//
//

#ifndef YCMainGamePassLayer_hpp
#define YCMainGamePassLayer_hpp

#include "cocos2d.h"
USING_NS_CC;
class MainGamePass:public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(MainGamePass);
private:
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
};
#endif /* YCMainGamePassLayer_hpp */
