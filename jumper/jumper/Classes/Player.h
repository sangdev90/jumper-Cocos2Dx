//
//  Player.h
//  jumper
//
//  Created by Alexander on 06.11.14.
//
//

#ifndef __jumper__Player__
#define __jumper__Player__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Player: public Sprite {
public:
    void jump();
    void slide();
    static Player* createPlayer();
private:

};

#endif /* defined(__jumper__Player__) */
