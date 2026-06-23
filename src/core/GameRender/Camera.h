#ifndef CAMERA_H
#define CAMERA_H

#include "../Math/Math.h"

struct Camera
{
    Vec2 position{0,0};
    float zoom = 1.0f;

    Rect worldToScreen(Rect worldRect) const
    {
        return
        {
            (worldRect.x - position.x) * zoom,
            (worldRect.y - position.y) * zoom,
            worldRect.w * zoom,
            worldRect.h * zoom
        };
    }
};

#endif
