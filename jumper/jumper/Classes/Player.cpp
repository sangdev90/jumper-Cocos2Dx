//
//  Player.cpp
//  jumper
//
//  Created by Alexander on 06.11.14.
//
//

#include "Player.h"
#include "cocos2d.h"

Player* Player::createPlayer(){
    auto player = Sprite::create("alkfly001.png");
    player->setAnchorPoint(Vec2(0, 0));
    player->setPosition(Vec2(100, 300));
    player->setScale(0.7, 0.7);
    return (Player*)player;
}

void Player::jump(){
    Vector<SpriteFrame*> animFrames(9);
    char str[100] = {0};
    for(int i = 1; i <= 9; i++)
    {
        sprintf(str, "alkjump0%d.png",i);
        auto frame = SpriteFrame::create(str,Rect(0, 0, 300, 200));
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);
    this->stopAllActions();
    auto completion = CallFunc::create([&](){
        this->slide();
    });
    this->runAction(Sequence::create(animate,completion, NULL));
}

void Player::slide(){
    Vector<SpriteFrame*> animFrames(3);
    char str[100] = {0};
    for (int i = 1; i<=3; i++){
        sprintf(str, "alkfly00%d.png",i);
        auto frame = SpriteFrame::create(str, Rect(0, 0, 300, 200));
        animFrames.pushBack(frame);
    }
    auto animtion = Animation::createWithSpriteFrames(animFrames,0.1f);
    auto slideAction = RepeatForever::create(Animate::create(animtion));
    this->runAction(RepeatForever::create(slideAction));
    
}
