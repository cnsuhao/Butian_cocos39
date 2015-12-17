//
//  YCHeroSprite.hpp
//  Butian
//
//  Created by apple on 15/11/22.
//
//

#ifndef YCHeroSprite_hpp
#define YCHeroSprite_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class HeroSprite : public cocos2d::Sprite
{
public:
    static HeroSprite* create();
    bool initSprite();
    b2Body *m_body;
};


#endif /* YCHeroSprite_hpp */
