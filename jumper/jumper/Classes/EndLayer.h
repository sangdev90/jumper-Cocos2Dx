//
//  EndLayer.h
//  jumper
//
//  Created by Alexander on 07.11.14.
//
//

#ifndef __jumper__EndLayer__
#define __jumper__EndLayer__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class EndLayer: public Layer {
public:
    static Scene* createSceneWithWin(bool won);
    virtual bool init();
    CREATE_FUNC(EndLayer);
};

#endif /* defined(__jumper__EndLayer__) */
