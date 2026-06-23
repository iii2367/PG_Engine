#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "../Math/Math.h"

struct SpriteSheet
{
    int textureId = -1;

    int frameCountX = 1;
    int animationCountY = 1;

    int textureWidth = 0;
    int textureHeight = 0;

    Rect getFrame(int frame, int animation) const
    {
        float frameW = textureWidth / frameCountX;

        float frameH = textureHeight / animationCountY;

        return
        {
            frame * frameW,
            animation * frameH,
            frameW,
            frameH
        };
    }
};

#endif
