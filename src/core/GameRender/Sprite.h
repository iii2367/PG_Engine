#ifndef SPRITE_H
#define SPRITE_H

#include "../../ports/GFXPort/GFXPort.h"

struct Sprite
{
    int textureId = -1;

    Rect rect;

    float angle = 0;

    FlipMode flip = FlipMode::NONE;
};

#endif
