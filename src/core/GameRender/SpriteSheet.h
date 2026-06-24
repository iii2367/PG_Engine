#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "../../ports/GFXPort/GFXPort.h"

struct SpriteSheet
{
    int textureId = -1;

    int frameCountX = 1;
    int animationCountY = 1;

    int frameWidth = 0;
    int frameHeight = 0; 

    Rect getFrame(int frame, int animation) const
    {
        return Rect
        {
            static_cast<float>(frame * frameWidth),
            static_cast<float>(animation * frameHeight),
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        };
    }    
};

#endif
