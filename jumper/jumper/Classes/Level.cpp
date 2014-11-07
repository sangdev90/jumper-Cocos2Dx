//
//  Level.cpp
//  jumper
//
//  Created by Alexander on 06.11.14.
//
//

#include "Level.h"

float levelData[1][LVL_SIZE] = {
    {0,1000,1500,1000,3000,1000,4500,1000,6000,3000},
    
};

Level* Level::createLevel(int lvlNum){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Level* lvl = (Level*)Layer::create();
    lvl->length = levelData[lvlNum][8];
    int j = 0;
    Rect pB[LVL_SIZE/2];
    for (int i=0;i<LVL_SIZE-1;i++) {
        
        if (i%2 != 0) {
//            lvl->physicsBounds[i] = levelData[lvlNum][i];
            continue;
        }
        if (i == LVL_SIZE-2) {
            Sprite* finLine = Sprite::create("finLine.png", Rect(0, 0, 30, 400));
            finLine->setName("finLine");
            finLine->setAnchorPoint(Vec2(0, 0));
            finLine->setPosition(Vec2(levelData[lvlNum][i]+300, 0));
            lvl->addChild(finLine);
        }
//        lvl->physicsBounds[i] = levelData[lvlNum][i];
        Sprite* groundBlock = Sprite::create("bTex.png", Rect(0, 0, levelData[lvlNum][i+1], 20));
        groundBlock->setName("grBlock");
        groundBlock->setAnchorPoint(Vec2(0, 0));
        groundBlock->setPosition(Vec2(levelData[lvlNum][i], 100));
        lvl->addChild(groundBlock);
//        Rect rect = Rect(levelData[lvlNum][i],100,levelData[lvlNum][i+1],20);
//        if ( j <= 4){
//            printf("%d",j);
//            pB[j] = rect;
//            j++;
//        }
    }
    
    
    return lvl;
}

Rect pB[LVL_SIZE/2];
Rect* Level::getPhysicsBoundsForLevel(int lvlNum){
    int j = 0;
    for (int i=0;i<LVL_SIZE-1;i++) {
        if (i%2 != 0) {
            //            lvl->physicsBounds[i] = levelData[lvlNum][i];
            continue;
        }
        //        lvl->physicsBounds[i] = levelData[lvlNum][i];
//        Sprite* groundBlock = Sprite::create("bTex.png", Rect(0, 0, levelData[lvlNum][i+1], 20));
//        groundBlock->setAnchorPoint(Vec2(0, 0));
//        groundBlock->setPosition(Vec2(levelData[lvlNum][i], 100));
//        lvl->addChild(groundBlock);
        Rect rect = Rect(levelData[lvlNum][i],100,levelData[lvlNum][i+1],5);
                if ( j <= 4){
//                    printf("%d",j);
                    pB[j] = rect;
                    j++;
                }
    }
    return pB;
}