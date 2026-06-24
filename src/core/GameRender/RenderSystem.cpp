#include "RenderSystem.h"

#include <algorithm>
#include <any>

RenderSystem::RenderSystem(IGFXPort& gfx) : gfx(&gfx) {}

void RenderSystem::submitSprite(RenderCommand cmd, Sprite sprite)
{
    CommandBuffer cmdBuf{cmd, sprite};
    cmdBuffer.push_back(cmdBuf);
}

void RenderSystem::sublitAnimated(RenderCommand cmd, SpriteSheet spriteSheet)
{
    CommandBuffer cmdBuf{cmd, spriteSheet};
    cmdBuffer.push_back(cmdBuf);
}

void RenderSystem::submitText(RenderCommand cmd)
{
    CommandBuffer cmdBuf{cmd, {}};
    cmdBuffer.push_back(cmdBuf);
}

void RenderSystem::setCamera(Camera& cam)
{
    camera = &cam;
}

void RenderSystem::present(float winW, float winH)
{
    std::sort(cmdBuffer.begin(), cmdBuffer.end(),
    [](const CommandBuffer& a, const CommandBuffer& b)
    {
        if (a.cmd.layer != b.cmd.layer) { return a.cmd.layer < b.cmd.layer; }
        return a.cmd.z < b.cmd.z;
    });
    
    for (auto cmd : cmdBuffer)
    {
        switch (cmd.cmd.type)
        {
            case RenderCommand::Type::Sprite:
            {
                auto sprite = std::any_cast<Sprite>(cmd.data);
                if (camera)
                {       
                    auto locdst = camera->worldToScreen(sprite.dst, winW, winH);
                    gfx->drawImageById(sprite.textureId, locdst, sprite.angle, sprite.flip);
                }
                else { gfx->drawImageById(sprite.textureId, sprite.dst, sprite.angle, sprite.flip); }
                break;
            }
            case RenderCommand::Type::Animated:
            {
                auto spriteSheet = std::any_cast<SpriteSheet>(cmd.data); 
                if (camera)
                {
                    auto locdst = camera->worldToScreen(spriteSheet.sprite.dst, winW, winH);
                    gfx->drawImageRegionById(spriteSheet.sprite.textureId, spriteSheet.sprite.src, locdst, spriteSheet.sprite.angle, spriteSheet.sprite.flip); 
                }
                else { gfx->drawImageRegionById(spriteSheet.sprite.textureId, spriteSheet.sprite.src, spriteSheet.sprite.dst, spriteSheet.sprite.angle, spriteSheet.sprite.flip); }
                break;
            }
            case RenderCommand::Type::Text:
            {
    
                break;
            }
        }
    }
    cmdBuffer.clear();
}
