#ifndef CAMERA_H
#define CAMERA_H

#include "../Math/Math.h"

struct Camera
{
    Vec2 position{0,0};
    float zoom = 1.0f;

    Rect worldToScreen(Rect worldRect, float winWidth, float winHeight) const
    {
        return
        {
            (worldRect.x - position.x) + winWidth/2,
            (worldRect.y - position.y) + winHeight/2,
            worldRect.w * zoom,
            worldRect.h * zoom
        };
    }
};

#endif
