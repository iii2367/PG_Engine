#ifndef SPRITE_H
#define SPRITE_H

#include "../../ports/GFXPort/GFXPort.h"

struct Sprite
{
    int textureId = -1;

    Rect src {0, 0, 0, 0};   
    Rect dst {0, 0, 0, 0};   

    float angle = 0;
    FlipMode flip = FlipMode::NONE;    
};

#endif
