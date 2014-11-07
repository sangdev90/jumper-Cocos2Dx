//
//  Level.h
//  jumper
//
//  Created by Alexander on 06.11.14.
//
//

#ifndef __jumper__Level__
#define __jumper__Level__

#include <stdio.h>
#include "cocos2d.h"

#define LVL_SIZE 10

using namespace cocos2d;

class Level: public Layer {
public:
    static Level* createLevel(int lvlNum);
    float length;
    static Rect* getPhysicsBoundsForLevel(int lvlNum);
    
};

#endif /* defined(__jumper__Level__) */
