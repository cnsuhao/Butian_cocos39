//
//  YCMainGameScene.cpp
//  Butian
//
//  Created by apple on 15/11/22.
//
//

#include "YCMainGameScene.hpp"
#include "../Sprites/YCWallSprite.hpp"
#include "../Sprites/YCHeroSprite.hpp"
#include "../Layers/YCMainGameMapLayer.hpp"
#include "../Extent/Macros.h"
#include "../Layers/YCMainGamePassLayer.hpp"
#include "../Layers/YCMainGameOverLayer.hpp"
#include "../Layers/YCMainGameFarViewLayer.hpp"

MainGameMap* MainGame::mapLayer;
MainGamePass* MainGame::passLayer;
GameOver* MainGame::gameOverLayer;
MainGameFarView* MainGame::farViewLayer;

Scene* MainGame::createScene(int chapter)
{
    auto scene = Scene::create();
    
    auto layer = MainGame::create();
    layer->m_chapter = chapter;
    scene->addChild(layer);
    
    //远景层
    farViewLayer = MainGameFarView::create();
    scene->addChild(farViewLayer);
    
    //map地图
    mapLayer = MainGameMap::create();
    scene->addChild(mapLayer);
    
    //过关层
    passLayer = MainGamePass::create();
    scene->addChild(passLayer);
    passLayer->setVisible(false);
    
    //游戏结束层
    gameOverLayer = GameOver::create();
    scene->addChild(gameOverLayer);
    gameOverLayer->setVisible(false);
    
    return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    isPass = false;
    isGameOver = false;
    
    //触摸事件注册
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainGame::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //WORLd
    b2Vec2 gravity;
    gravity.Set(0.0f, G);
    m_world = new b2World(gravity);
    
    //碰撞事件注册
    contactListener = new ContactListener();
    contactListener->mainLayer = this;
    m_world->SetContactListener(contactListener);

    
    //开启调试模式
    _debugDraw = new GLESDebugDraw(PTM_RATIO);
    m_world->SetDebugDraw(_debugDraw);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    _debugDraw->SetFlags(flags);
    
    //定时函数
    schedule(schedule_selector(MainGame::tick));

    return true;
}

void MainGame::onEnterTransitionDidFinish() {
    //装载地图
    mapLayer->m_world = m_world;
    __String *chapterSTR = __String::createWithFormat("Chapters/chapter%i.plist",m_chapter);
    mapLayer->loadMap(chapterSTR->getCString());
    //游戏开始，先让玩家看到终点在哪里
    mapLayer->seeDoor();
}

#pragma mark - tick
void MainGame::tick(float dt) {
    int velocityIterations = 8;
    int positionIterations = 1;
    m_world->Step(dt, velocityIterations, positionIterations);
    //目前只能理解为刷新屏幕，有些概念太难理解，要慢慢来
    for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            Sprite* myActor = (Sprite*)b->GetUserData();
            myActor->setPosition(Vec2( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
    
    if (!isPass) {
        mapLayer->adjustMap();
        if (mapLayer->m_heroSprite!=NULL) {
            farViewLayer->adjustFarView(mapLayer->m_heroSprite->getPosition(),mapLayer->mapSize);
        }
        //mapLayer->keepHeroVertical();
    }else {
        unschedule(schedule_selector(MainGame::tick));
    }
}

#pragma mark - touch
bool MainGame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if (isPass||isGameOver) {//过关后停止触摸
        return false;
    }
    else {
        return true;
    }
}

void MainGame::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    
}

void MainGame::onTouchEnded(cocos2d::Touch *touches, cocos2d::Event *event) {
    auto point = touches->getLocationInView();
    point = Director::getInstance()->convertToGL(point);
    mapLayer->refreshMap(point);
}

#pragma mark - 调试
void MainGame::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    m_world->DrawDebugData();
    CHECK_GL_ERROR_DEBUG();
}

#pragma mark - 碰撞处理
void MainGame::beginContactFun(b2Contact *contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Sprite* spriteA = (Sprite*)bodyA->GetUserData();
    Sprite* spriteB = (Sprite*)bodyB->GetUserData();
    __String spriteAName;
    __String spriteBName;
    if (spriteA!=NULL) {
        spriteAName = spriteA->getName();
    }
    if (spriteB!=NULL) {
        spriteBName = spriteB->getName();
    }
    
    if (spriteAName.compare(HERO_SPRITE_MACRO)==0&&spriteBName.compare(DOOR_SPRITE_MACRO)==0) {//碰撞到能量们，过关
        passGame();
    }
    if (spriteAName.compare(DOOR_SPRITE_MACRO)==0&&spriteBName.compare(HERO_SPRITE_MACRO)==0) {//碰撞到能量们，过关
        passGame();
    }
    
    if (spriteAName.compare(HERO_SPRITE_MACRO)==0&&spriteBName.compare(ENEMY_SPRITE_MACRO)==0) {//撞到敌人，结束游戏
        gameOver();
    }
    if (spriteAName.compare(ENEMY_SPRITE_MACRO)==0&&spriteBName.compare(HERO_SPRITE_MACRO)==0) {//撞到敌人，结束游戏
        gameOver();
    }
    
    if (spriteAName.compare(HERO_SPRITE_MACRO)==0&&spriteBName.compare(WAll_SPRITE_MACRO)==0) {//撞到墙
        float difX = fabsf(spriteA->getPosition().x-spriteB->getPosition().x);
        float difY = fabsf(spriteA->getPosition().y-spriteB->getPosition().y);
        if (difX>difY) {//撞到墙
            hitWall(0);
        }else {//撞到地
            hitWall(1);
        }
    }
    if (spriteAName.compare(WAll_SPRITE_MACRO)==0&&spriteBName.compare(HERO_SPRITE_MACRO)==0) {//撞到墙
        float difX = fabsf(spriteA->getPosition().x-spriteB->getPosition().x);
        float difY = fabsf(spriteA->getPosition().y-spriteB->getPosition().y);
        if (difX>difY) {//撞到墙
            hitWall(0);
        }else {//撞到地
            hitWall(1);
        }
    }
}

#pragma mark - 过关,游戏结束

void MainGame::passGame() {
    if (!isPass) {
        isPass = true;
        passLayer->setVisible(true);
        int chapter = (m_chapter+1)%TOTAL_CHAPTER;
        auto nextChapter = MainGame::createScene(chapter);
        auto nextChapterAct = TransitionTurnOffTiles::create(1, nextChapter);
        Director::getInstance()->replaceScene(nextChapterAct);
//        ActionInterval * scaleAction = ScaleTo::create(1.2, 1.2);
//        ActionInterval * moveToAction = MoveTo::create(1.2, Vec2(visibleSize.width/2-mapLayer->m_heroSprite->getPositionX(), visibleSize.height/2-mapLayer->m_heroSprite->getPositionY()));
//        FiniteTimeAction * spawn = Spawn::create(scaleAction,moveToAction, NULL);
//        mapLayer->runAction(spawn);
    }
}

void MainGame::gameOver() {
    if (!isGameOver) {
        isGameOver = true;
        passLayer->setVisible(true);
        auto nextChapter = MainGame::createScene(m_chapter);
        auto nextChapterAct = TransitionTurnOffTiles::create(1, nextChapter);
        Director::getInstance()->replaceScene(nextChapterAct);
    }
}

#pragma mark - 英雄撞墙

void MainGame::hitWall(int type) {
    if (type==0) {//墙
        mapLayer->playHeroFrames(HERO_HIT_WALL_ACTION, 4);
        mapLayer->giveImpulse();
    } else if (type==1) {
        mapLayer->playHeroFrames(HERO_HIT_GROUND_ACTION, 4);
    }
    
}
