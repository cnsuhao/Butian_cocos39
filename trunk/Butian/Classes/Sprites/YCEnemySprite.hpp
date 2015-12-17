//
//  YCEnemySprite.hpp
//  Butian
//
//  Created by apple on 15/12/6.
//
//

#ifndef YCEnemySprite_hpp
#define YCEnemySprite_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class EnemySprite : public cocos2d::Sprite
{
public:
    static EnemySprite* create(const char* imgName);
    bool initSprite();
    b2Body *m_body;
private:
    const char*imgName;
};


#endif /* YCEnemySprite_hpp */
