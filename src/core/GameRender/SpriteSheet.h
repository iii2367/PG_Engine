#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "../Math/Math.h"

struct SpriteSheet
{
    int textureId = -1;

    int frameCountX = 1;
    int animationCountY = 1;

    Rect rect {0, 0, 0, 0};

    float frameW = 0;
    float frameH = 0;

    void setSizeFrame()
    {
        frameW = rect.w / frameCountX;
        frameH = rect.h / animationCountY;
    }

    Rect getFrame(int frame, int animation) const
    {
        return
        {
            rect.w + frame * frameW,
            rect.h + animation * frameH,
            frameW,
            frameH
        };
    }
};

#endif
