//
//  GameScene.h
//  jumper
//
//  Created by Alexander on 06.11.14.
//
//

#ifndef __jumper__GameScene__
#define __jumper__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "Player.h"
#include "Level.h"
using namespace cocos2d;

class GameLayer : public LayerColor{
public:
    static Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(GameLayer);
    
private:
    Layer* bgLayer;
    
    Player* player;
    
    Level* level;
    
    Label* scLbl;
    
    int score;
    
    void update(float dt);
    void gameOver(bool won);
    
    void generateCoins();
};

#endif /* defined(__jumper__GameScene__) */
