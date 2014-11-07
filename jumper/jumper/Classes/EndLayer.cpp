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

Scene* EndLayer::createSceneWithWin(bool won){
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
    
    
    return scene;
}

bool EndLayer::init() {
    if (!Layer::init()){
        return false;
    }
    
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto startLabel = Label::createWithSystemFont("Tap on screen to Restart", "Helvetica", 40);
    startLabel->setPosition(visibleSize.width/2, visibleSize.height/2);
    startLabel->setZOrder(10);
    this->addChild(startLabel);
    
    return true;
}









