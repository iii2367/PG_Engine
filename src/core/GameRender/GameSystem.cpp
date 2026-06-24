#include "GameSystem.h"

RenderSystem::RenderSystem(IGFXPort& gfx) : gfx(gfx) {}

Camera& RenderSystem::getCamera() { return camera; }

void RenderSystem::drawSprite(int textureId, Rect worldRect)
{
    //Rect screen = camera.worldToScreen(worldRect);
    //gfx.drawImageById(textureId, screen, 0, FlipMode::NONE);
}

void RenderSystem::drawAnimated(AnimatedSprite& anim, Rect worldRect, float winX, float winY)
{
 //   Rect src = anim.getSourceRect();
 //   Rect dst = camera.worldToScreen(worldRect, winX, winY);
 //   gfx.drawImageRegionById(anim.sheet.textureId, src, dst, 0, FlipMode::NONE);
}
