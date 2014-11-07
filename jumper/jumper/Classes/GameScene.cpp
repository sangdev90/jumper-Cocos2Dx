//
//  GameScene.cpp
//  jumper
//
//  Created by Alexander on 06.11.14.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "EndLayer.h"

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
    this->score = 0;
    this->bgLayer = Layer::create();
    this->addChild(this->bgLayer);
    this->level = Level::createLevel(0);
    this->level->runAction(MoveBy::create(7, Vec2(-this->level->length-1000, 0)));
    this->addChild(this->level);
    
    this->generateCoins();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backgroundMusic.mp3");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->scLbl = Label::createWithSystemFont("0", "Helvetica", 40);
    this->scLbl->setPosition(visibleSize.width/2, visibleSize.height-30);
    this->scLbl->setZOrder(10);
    this->addChild(this->scLbl);
    
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
    bool touchedGround = false;
    bool gameWon = false;
    bool catchCoin = false;
    Rect *phB = Level::getPhysicsBoundsForLevel(0);
    Rect plR = Rect(this->player->getPosition().x, this->player->getPosition().y, this->player->getContentSize().width, 20);
//    for (int i = 0; i < LVL_SIZE/2 ;i++){
//        Rect r = phB[i];
////        touchedGround = plR.intersectsRect(Rect(0,100,1000, 50));
////        printf("rx:%f,y:%f,w:%f,h:%f",r.origin.x,r.origin.y,r.size.width,r.size.height);
////        printf("plRx:%f,y:%f,w:%f,h:%f",plR.origin.x,plR.origin.y,plR.size.width,plR.size.height);
//    }
//    bool *t = &touchedGround;
    this->level->enumerateChildren("grBlock", [&](Node* node){
        Sprite *spr = (Sprite*)node;
        float offset = -this->level->getPosition().x;
//        printf("%f",offset);
        Rect r = Rect(spr->getPosition().x-offset, spr->getPosition().y-50, spr->getContentSize().width, 20);
        touchedGround = plR.intersectsRect(r);
        return touchedGround;
    });
    this->level->enumerateChildren("finLine", [&](Node* node){
        Sprite *spr = (Sprite*)node;
        float offset = -this->level->getPosition().x;
        //        printf("%f",offset);
        Rect r = Rect(spr->getPosition().x-offset+300, spr->getPosition().y-50, 30, 400);
        gameWon = plR.intersectsRect(r);
        return gameWon;
    });
    Sprite* toRemove[40];
    for (int i=0; i<40;i++){
        toRemove[i] = Sprite::create();
    }
    int j = 0;
    this->level->enumerateChildren("coin", [&](Node* node){
        Sprite *spr = (Sprite*)node;
        float offset = -this->level->getPosition().x;
        //        printf("%f",offset);
        Rect r = Rect(spr->getPosition().x-offset, spr->getPosition().y-50, 10, 10);
        catchCoin = plR.intersectsRect(r);
//        spr->removeFromParent();
        if(catchCoin)toRemove[j]=spr;
        j++;
        return catchCoin;
    });
    for(int i =0; i<30;i++){
        Sprite *spr = toRemove[i];
        if (spr->getTexture()!=NULL){
            spr->removeFromParent();
        }
    }
    if( catchCoin ) {
        this->score+=1;
    }
    char scoreTxt[100] = {0};
    sprintf(scoreTxt, "your score %d",this->score);
    this->scLbl->setString(scoreTxt);
    if(gameWon){
        this->gameOver();
    }
    static float v0 = 0;
//    allTime += dt;
    float v = v0 + a*dt;
    float y = v*dt;
    if (this->player->getPosition().y < -50 ){
        v0=0;
        this->gameOver();
//        this->player->setPosition(Vec2(player->getPosition().x, -100));
    }else if(touchedGround){
        v0=0;
    }else if (affectGravity) {
        this->player->setPosition(Vec2(player->getPosition().x, player->getPosition().y+y));
        v0=v;
    }
}

void GameLayer::generateCoins(){
    for (int i=0;i<20;i++){
        Sprite* coin = Sprite::create("coin_001.png");
        coin->setAnchorPoint(Vec2(0, 0));
        coin->setPosition(Vec2(300*(i+1), 300));
        coin->setZOrder(10);
        coin->setName("coin");
        this->level->addChild(coin);
    }
}

void GameLayer::gameOver(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    auto scene = EndLayer::createSceneWithWin(false);
    auto transition = TransitionFade::create(0.4, scene);
    Director::getInstance()->replaceScene(transition);
}

