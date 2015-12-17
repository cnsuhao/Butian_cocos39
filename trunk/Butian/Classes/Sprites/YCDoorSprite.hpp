//
//  YCDoorSprite.hpp
//  Butian
//
//  Created by apple on 15/12/1.
//
//

#ifndef YCDoorSprite_hpp
#define YCDoorSprite_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class DoorSprite : public cocos2d::Sprite
{
public:
    static DoorSprite* create(const char* imgName);
    bool initSprite();
    b2Body *m_body;
private:
    const char*imgName;
};

#endif /* YCDoorSprite_hpp */
