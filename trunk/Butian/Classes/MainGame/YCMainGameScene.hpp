//
//  YCMainGameScene.hpp
//  Butian
//
//  Created by apple on 15/11/22.
//
//

#ifndef YCMainGameScene_hpp
#define YCMainGameScene_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../GLES-Render.h"
#include "../Extent/YCCollision.h"

USING_NS_CC;
class MainGameMap;
class MainGamePass;
class GameOver;
class MainGameFarView;
class HeroSprite;

class MainGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int chapter);
    virtual bool init();
    CREATE_FUNC(MainGame);
    void beginContactFun(b2Contact *contact);
    int m_chapter; //第几关
private:
    //触摸
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onEnterTransitionDidFinish();
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);//调试
    void passGame();
    void gameOver();
    void hitWall(int type);
    void tick(float dt);
    b2World *m_world;
    Size visibleSize;
    Vec2 origin;
    bool isPass; //是否已经过关
    bool isGameOver; //是否已经结束游戏
    GLESDebugDraw *_debugDraw;
    ContactListener *contactListener;
    //layers
    static MainGameMap *mapLayer;
    static MainGamePass *passLayer;
    static GameOver *gameOverLayer;
    static MainGameFarView *farViewLayer;
};

#endif /* YCMainGameScene_hpp */
