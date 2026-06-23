#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "../../ports/GFXPort/GFXPort.h"
#include "Camera.h"
#include "AnimatedSprite.h"

class RenderSystem
{
public:
    explicit RenderSystem(IGFXPort& gfx);
    Camera& getCamera();
    void drawSprite(int textureId, Rect worldRect);
    void drawAnimated(AnimatedSprite& anim, Rect worldRect, float winX, float winY); 
private:

    IGFXPort& gfx;
public:
    Camera camera;
};

#endif
