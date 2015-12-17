//
//  YCMainGameMapLayer.cpp
//  Butian
//
//  Created by apple on 15/11/29.
//
//

#include "YCMainGameMapLayer.hpp"
#include "../Sprites/YCWallSprite.hpp"
#include "../Sprites/YCHeroSprite.hpp"
#include "../Extent/Macros.h"
#include "../Sprites/YCDoorSprite.hpp"
#include "../Sprites/YCEnemySprite.hpp"

bool MainGameMap::init() {
    if (!Layer::init()) {
        return false;
    }
    
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();
    isSeeDoorOver = false;
    
    //装载墙图像
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("wall.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero1.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("door.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("wind.plist");
    
    return true;
}

#pragma mark - 创建地图方块

void MainGameMap::loadMap(const char *chapterName) {
    //读取关卡plist文件
    FileUtils *file=FileUtils::getInstance();
    auto info = file->getValueMapFromFile(chapterName);
    auto wallarray = info["wallarray"].asValueVector();//地图
    for (int i=0; i<wallarray.size(); i++) {
        Value::Type type = wallarray.at(i).getType();
        if (type==Value::Type::MAP) {
            auto wall = wallarray.at(i).asValueMap();
            float x = wall["x"].asFloat();
            float y = wall["y"].asFloat();
            float width = wall["width"].asFloat();
            float height = wall["height"].asFloat();
            __String imgSTR = wall["imagename"].asString();
            builtWall(x, y, width, height, imgSTR.getCString());
        }
    }
    
    //初始化主角
    auto hero = info["hero"].asValueMap();
    float x = hero["x"].asFloat();
    float y = hero["y"].asFloat();
    float width = hero["width"].asFloat();
    float height = hero["height"].asFloat();
    builtHero(x, y, width, height);
    
    //初始出口,过关
    auto door = info["door"].asValueMap();
    x = door["x"].asFloat();
    y = door["y"].asFloat();
    width = door["width"].asFloat();
    height = door["height"].asFloat();
    builtDoor(x, y, width, height);
    
    //初始化敌人
    if (info["sEnemy"].getType()==Value::Type::MAP) {
        auto enemyarray = info["sEnemy"].asValueVector();
        for (int i=0; i<enemyarray.size(); i++) {
            Value::Type type = enemyarray.at(i).getType();
            if (type==Value::Type::MAP) {
                auto wall = enemyarray.at(i).asValueMap();
                float x = wall["x"].asFloat();
                float y = wall["y"].asFloat();
                float width = wall["width"].asFloat();
                float height = wall["height"].asFloat();
                __String imgSTR = wall["imagename"].asString();
                builtEnemy(x, y, width, height, imgSTR.getCString());
            }
        }
    }
    
    //地图大小
    if (info["mapsize"].getType()==Value::Type::MAP) {
        auto mapSizeMap = info["mapsize"].asValueMap();
        mapSize.width = mapSizeMap["width"].asFloat();
        mapSize.height = mapSizeMap["height"].asFloat();
    }
}

void MainGameMap::builtWall(float x, float y, float width, float height, const char *imgName) {
    WallSprite* wallSprite = WallSprite::create(imgName);
    wallSprite->setPosition(Vec2(origin.x+x, origin.y+y));
    wallSprite->setScale(width/wallSprite->getContentSize().width,height/wallSprite->getContentSize().height);
    this->addChild(wallSprite);
    
    b2PolygonShape dwallShape;
    dwallShape.SetAsBox(width/2/PTM_RATIO, height/2/PTM_RATIO);
    b2FixtureDef dwallFixtureDef;
    dwallFixtureDef.shape = &dwallShape;
    dwallFixtureDef.density = 10;
    dwallFixtureDef.restitution = 0.1f;
    dwallFixtureDef.friction = 0.5;
    b2BodyDef dwallBodyDef;
    dwallBodyDef.type = b2_staticBody;
    dwallBodyDef.position.Set(wallSprite->getPositionX()/PTM_RATIO, wallSprite->getPositionY()/PTM_RATIO);
    b2Body* dwallBody = m_world->CreateBody(&dwallBodyDef);
    dwallBody->SetUserData(wallSprite);
    dwallBody->CreateFixture(&dwallFixtureDef);
}

void MainGameMap::builtHero(float x, float y, float width, float height) {
    m_heroSprite = HeroSprite::create();
    m_heroSprite->setPosition(Vec2(origin.x+x, origin.y+y));
    m_heroSprite->setScale(width/m_heroSprite->getContentSize().width,height/m_heroSprite->getContentSize().height);
    this->addChild(m_heroSprite);
    
    b2CircleShape shape;
    shape.m_radius = width/2/2/PTM_RATIO;
    //b2PolygonShape shape;
    //shape.SetAsBox(width/2/PTM_RATIO, height/2/PTM_RATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.restitution = 0.3f;//弹性系数
    fixtureDef.friction = 1.0f;//摩擦力
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_heroSprite->getPositionX()/PTM_RATIO, m_heroSprite->getPositionY()/PTM_RATIO);
    m_heroBody = m_world->CreateBody(&bodyDef);
    m_heroBody->SetUserData(m_heroSprite);
    m_heroBody->CreateFixture(&fixtureDef);
}

void MainGameMap::builtDoor(float x, float y, float width, float height) {
    m_doorSprite = DoorSprite::create("door_0.png");
    m_doorSprite->setPosition(Vec2(origin.x+x, origin.y+y));
    m_doorSprite->setScale(width/m_doorSprite->getContentSize().width,height/m_doorSprite->getContentSize().height);
    this->addChild(m_doorSprite);
    
    b2PolygonShape shape;
    //乘0.5调小些门，让碰撞看起来更真
    shape.SetAsBox(width*0.5/2/PTM_RATIO, height*0.58/2/PTM_RATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 10;
    fixtureDef.restitution = 0.1f;//弹性系数
    fixtureDef.friction = 0.9f;//摩擦力
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(m_doorSprite->getPositionX()/PTM_RATIO, m_doorSprite->getPositionY()/PTM_RATIO);
    m_doorBody = m_world->CreateBody(&bodyDef);
    m_doorBody->SetUserData(m_doorSprite);
    m_doorBody->CreateFixture(&fixtureDef);
}

void MainGameMap::builtEnemy(float x, float y, float width, float height,const char*imgName) {
    EnemySprite* sprite = EnemySprite::create(imgName);
    sprite->setPosition(Vec2(origin.x+x, origin.y+y));
    sprite->setScale(width/sprite->getContentSize().width,height/sprite->getContentSize().height);
    this->addChild(sprite);
    
    b2PolygonShape dwallShape;
    dwallShape.SetAsBox(width/2/PTM_RATIO, height/2/PTM_RATIO);
    b2FixtureDef dwallFixtureDef;
    dwallFixtureDef.shape = &dwallShape;
    dwallFixtureDef.density = 10;
    dwallFixtureDef.restitution = 0.1f;
    dwallFixtureDef.friction = 1.0;
    b2BodyDef dwallBodyDef;
    dwallBodyDef.type = b2_staticBody;
    dwallBodyDef.position.Set(sprite->getPositionX()/PTM_RATIO, sprite->getPositionY()/PTM_RATIO);
    b2Body* dwallBody = m_world->CreateBody(&dwallBodyDef);
    dwallBody->SetUserData(sprite);
    dwallBody->CreateFixture(&dwallFixtureDef);
}

#pragma mark - 调整map位置,主角位置
void MainGameMap::refreshMap(Point point) {
    if (m_heroSprite==NULL||!isSeeDoorOver) {
        return;
    }
    Vec2 centerOld = m_heroSprite->getPosition();
    //因为mapLayer坐标已经改变，所以要转换
    Vec2 center = Vec2(centerOld.x+this->getPositionX(), centerOld.y+this->getPositionY());
    float distance = point.getDistance(center);
    float cos=(point.x-center.x)/distance;
    float sin=(point.y-center.y)/distance;
    //以一定角度给主角施加一个冲量
    m_heroBody->ApplyLinearImpulse(b2Vec2(Init_Impulse*cos, Init_Impulse*sin), m_heroBody->GetWorldCenter(), true);
}

void MainGameMap::adjustMap() {
    //调整地图
    if (m_heroSprite==NULL||!isSeeDoorOver) {
        return;
    }
    
    float adjustX = visibleSize.width/2-m_heroSprite->getPositionX();
    float adjustY = visibleSize.height/2-m_heroSprite->getPositionY();
    
    if (adjustX>0) {
        adjustX = 0;
    }
    if (adjustY>0) {
        adjustY = 0;
    }
    if (-adjustX>mapSize.width-visibleSize.width) {
        adjustX = visibleSize.width-mapSize.width;
    }
    if (-adjustY>mapSize.height-visibleSize.height) {
        adjustY = visibleSize.height-mapSize.height;
    }
    
    this->setPosition(Point(adjustX,adjustY));
    //m_heroBody->SetTransform(m_heroBody->GetPosition(), 0);
    //m_heroSprite->setRotation(0);
}

void MainGameMap::giveImpulse() {
    if (m_heroSprite==NULL) {
        return;
    }
    m_heroBody->ApplyLinearImpulse(b2Vec2(0, Init_Impulse*0.5), m_heroBody->GetWorldCenter(), true);
}

void MainGameMap::seeDoor() {
    if (m_heroSprite==NULL||m_doorSprite==NULL) {
        return;
    }
    
    Point point = m_doorSprite->getPosition();
    ActionInterval *actionTo = MoveTo::create(1.0, Vec2(origin.x+visibleSize.width/2-point.x, origin.y+visibleSize.height/2-point.y));
    this->runAction(actionTo);
    scheduleOnce(schedule_selector(MainGameMap::backToHero), 2.0f);
}

void MainGameMap::backToHero(float dt) {
    Point point = Point::ZERO;
    ActionInterval *actionTo = MoveTo::create(1.0, point);
    this->runAction(actionTo);
    scheduleOnce(schedule_selector(MainGameMap::overSeeDoor), 2.2f);
}

void MainGameMap::overSeeDoor(float dt) {
    isSeeDoorOver = true;
}

void MainGameMap::playHeroFrames(const char *ImgName, int fNum) {
    if (m_heroSprite==NULL) {
        return;
    }
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    for (int i=0; i<fNum; i++) {
        __String *str = __String::createWithFormat("%s_%i.png",ImgName,i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
        frames.pushBack(frame);
    }
    Animation *animation = Animation::createWithSpriteFrames(frames,1.0f/24.0f);
    animation->setRestoreOriginalFrame(true);
    Animate *animate = Animate::create(animation);
    m_heroSprite->runAction(animate);
    //m_heroSprite->runAction(RepeatForever::create(animate));
}

void MainGameMap::keepHeroVertical() {
    if (m_heroSprite==NULL) {
        return;
    }
    m_heroSprite->setRotation(0);
}
