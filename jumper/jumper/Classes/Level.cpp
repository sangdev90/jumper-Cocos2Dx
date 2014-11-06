//
//  Level.cpp
//  jumper
//
//  Created by Alexander on 06.11.14.
//
//

#include "Level.h"


Level* Level::createLevel(int lvlNum){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float levelData[5][10] = {
        {0,1000,1200,1000,2400,1000,3600,1000,4800,1000},
        {0,300,325,725,750,1150,1175,1350,1375,1700},
        {0,300,325,725,750,1150,1175,1350,1375,1700},
        {0,300,325,725,750,1150,1175,1350,1375,1700},
        {0,300,325,725,750,1150,1175,1350,1375,1700}
    };
    Level* lvl = (Level*)Layer::create();
    lvl->length = levelData[lvlNum][9]+levelData[lvlNum][8]-visibleSize.width;
    printf("i-%f\n",lvl->length);
    for (int i=0;i<9;i++) {
        if (i%2 != 0) continue;
        Sprite* groundBlock = Sprite::create("bTex.png", Rect(0, 0, levelData[lvlNum][i+1], 20));
        groundBlock->setAnchorPoint(Vec2(0, 0));
        groundBlock->setPosition(Vec2(levelData[lvlNum][i], 100));
        lvl->addChild(groundBlock);
    }
    
    
    return lvl;
}