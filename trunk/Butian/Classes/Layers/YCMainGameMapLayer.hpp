//
//  YCMainGameMapLayer.hpp
//  Butian
//
//  Created by apple on 15/11/29.
//
//

#ifndef YCMainGameMapLayer_hpp
#define YCMainGameMapLayer_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;

class HeroSprite;
class DoorSprite;

class MainGameMap:public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(MainGameMap);
    void loadMap(const char* chapterName);
    b2World *m_world;
    HeroSprite* m_heroSprite;//主角
    void refreshMap(Point point);
    void adjustMap();
    void seeDoor(); //游戏开始后移动到门
    void giveImpulse();//给英雄施加向上的冲量
    //播放英雄动画
    void playHeroFrames(const char*ImgName,int fNum);
    void keepHeroVertical();
    Size mapSize; //地图大小
private:
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
    void builtWall(float x,float y,float width,float height,const char*imgName);
    void builtHero(float x,float y,float width,float height);
    void builtDoor(float x,float y,float width,float height);
    void builtEnemy(float x,float y,float width,float height,const char*imgName);
    void backToHero(float dt); //从门移动回主角
    void overSeeDoor(float dt); //看门结束
    b2Body* m_heroBody;
    DoorSprite* m_doorSprite;//门，过关
    b2Body* m_doorBody;
    bool isSeeDoorOver;
};

#endif /* YCMainGameMapLayer_hpp */
