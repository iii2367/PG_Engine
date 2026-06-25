#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "../../ports/GFXPort/GFXPort.h"
#include "Sprite.h"

struct SpriteSheet
{
    Sprite sprite{};

    int frameCountX = 1;
    int frameCountY = 1;

    int frameWidth = 0;
    int frameHeight = 0; 

    void getFrame(int frame, int animation)
    {
        sprite.src.x = static_cast<float>(frame * frameWidth);
        sprite.src.y = static_cast<float>(animation * frameHeight);
        sprite.src.w = static_cast<float>(frameWidth);
        sprite.src.h = static_cast<float>(frameHeight);
    }    
};

#endif
