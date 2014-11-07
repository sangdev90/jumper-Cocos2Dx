//
//  EndLayer.cpp
//  jumper
//
//  Created by Alexander on 07.11.14.
//
//

#include "EndLayer.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

Scene* EndLayer::createSceneWithWin(bool won,int score){
    Scene *scene = Scene::create();
    EndLayer* layer = EndLayer::create();
    Sprite *bg;
    if (won) {
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
        bg = Sprite::create("YouWin.png");
        bg->setScale(0.7, 0.7);
//        bg->setContentSize(Size(300, 400));
    } else {
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
        bg = Sprite::create("YouLose.png");
        bg->setScale(0.7, 0.7);
//        printf("qq%f,%f",visibleSize.width,visibleSize.height);
    }
    bg->setPosition(Vec2(0, 0));
    bg->setAnchorPoint(Vec2(0, 0));
    layer->addChild(bg);
    scene->addChild(layer);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    char scoreTxt[100] = {0};
    sprintf(scoreTxt, "your score %d",score);
    auto scLbl = Label::createWithSystemFont(scoreTxt, "Helvetica", 60);
    scLbl->setPosition(visibleSize.width/2, visibleSize.height-200);
    scLbl->setZOrder(10);
    layer->addChild(scLbl);
    return scene;
}

bool EndLayer::init() {
    if (!Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    //    auto pl = this->player;
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [](Touch* touch, Event* event){
        auto scene = GameLayer::createScene();
        auto transition = TransitionFade::create(0.4, scene);
        Director::getInstance()->replaceScene(transition);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto startLabel = Label::createWithSystemFont("Tap on screen to Restart", "Helvetica", 40);
    startLabel->setPosition(visibleSize.width/2, visibleSize.height/2);
    startLabel->setZOrder(10);
    this->addChild(startLabel);
    
    return true;
}









