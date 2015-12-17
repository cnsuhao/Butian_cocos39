//
//  YCMainGameOverLayer.hpp
//  Butian
//
//  Created by apple on 15/12/6.
//
//

#ifndef YCMainGameOverLayer_hpp
#define YCMainGameOverLayer_hpp

#include "cocos2d.h"
USING_NS_CC;
class GameOver:public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(GameOver);
private:
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
};


#endif /* YCMainGameOverLayer_hpp */
