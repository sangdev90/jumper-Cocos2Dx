//
//  GameScene.cpp
//  jumper
//
//  Created by Alexander on 06.11.14.
//
//

#include "GameScene.h"

float a = -980;
bool affectGravity = true;

Scene* GameLayer::createScene(){
    auto scene = Scene::create();
    auto gameLayer = GameLayer::create();
    scene->addChild(gameLayer);
    return scene;
}

bool GameLayer::init(){
    if (!LayerColor::initWithColor(Color4B(100, 200, 100, 255))){
        return false;
    }
    this->bgLayer = Layer::create();
    this->addChild(this->bgLayer);
    this->level = Level::createLevel(0);
    this->level->runAction(MoveBy::create(7, Vec2(-this->level->length, 0)));
    this->addChild(this->level);
    
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    Texture2D bgTexture = Texture2D();
//    Image bgImg ;
//    bgImg.initWithImageFile("bg.png");
//    bgTexture.initWithImage(&bgImg);
    int i=0;
    for (i=0;i<2;i++){
        auto bg = Sprite::create("bg.png");
        bg->setName("bgSprite");
        bg->setAnchorPoint(Vec2(0,0));
        bg->setPosition(Vec2(bg->getContentSize().width*i, 0));
        this->bgLayer->addChild(bg);
        
        auto action = MoveBy::create(10, Vec2(-bg->getContentSize().width, 0));
        auto revAction = MoveBy::create(0, Vec2(bg->getContentSize().width,0));
        auto seq = Sequence::create(action,revAction, NULL);
        auto infinite = RepeatForever::create(seq);
        
        bg->runAction(infinite);
    }
    
    this->player = Player::createPlayer();
    this->player->slide();
    this->addChild(player);
    
    auto touchListener = EventListenerTouchOneByOne::create();
//    auto pl = this->player;
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        auto action = MoveBy::create(0.1, Vec2(0, 200));
        auto completion = CallFunc::create([](){
            affectGravity = true;
        });
        this->player->jump();
        this->player->runAction(Sequence::create(action,completion, NULL));
        affectGravity = false;
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->schedule(schedule_selector(GameLayer::update));
    return true;
}

void GameLayer::update(float dt){
//    static float allTime = 0;
    static float v0 = 0;
//    allTime += dt;
    float v = v0 + a*dt;
    float y = v*dt;
    if (this->player->getPosition().y < -50 ){
        v0=0;
//        this->player->setPosition(Vec2(player->getPosition().x, -100));
    } else if (affectGravity) {
        this->player->setPosition(Vec2(player->getPosition().x, player->getPosition().y+y));
        v0=v;
    }
}

void GameLayer::gameOver(){
    
}

