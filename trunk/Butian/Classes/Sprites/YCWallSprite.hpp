//
//  YCWallSprite.hpp
//  Butian
//
//  Created by apple on 15/11/22.
//
//

#ifndef YCWallSprite_hpp
#define YCWallSprite_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class WallSprite : public cocos2d::Sprite
{
public:
    static WallSprite* create(const char* imgName);
    bool initSprite();
    b2Body *m_body;
private:
    const char*imgName;
};

#endif /* YCWallSprite_hpp */
