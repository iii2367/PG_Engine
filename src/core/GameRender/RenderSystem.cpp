#include "RenderSystem.h"
#include "PlayLoad.h"

#include <algorithm>
#include <any>

RenderSystem::RenderSystem(IGFXPort& gfx) : gfx(&gfx) {}

void RenderSystem::submitSprite(RenderCommand cmd, Sprite sprite)
{
    CommandBuffer cmdBuf{cmd, SpritePayload{sprite}};
    cmdBuffer.push_back(cmdBuf);
}

void RenderSystem::sublitAnimated(RenderCommand cmd, SpriteSheet spriteSheet)
{
    CommandBuffer cmdBuf{cmd, AnimatedPayload{spriteSheet}};
    cmdBuffer.push_back(cmdBuf);
}

void RenderSystem::submitText(RenderCommand cmd, Text text)
{
    CommandBuffer cmdBuf{cmd, TextPayload{text}};
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
                const auto& payload = std::get<SpritePayload>(cmd.data);
                const auto& sprite = payload.sprite;
                if (camera && cmd.cmd.layer != RenderLayer::HUD)
                {       
                    auto locdst = camera->worldToScreen(sprite.dst, winW, winH);
                    gfx->drawImageById(sprite.textureId, locdst, sprite.angle, sprite.flip);
                }
                else { gfx->drawImageById(sprite.textureId, sprite.dst, sprite.angle, sprite.flip); }
                break;
            }
            case RenderCommand::Type::Animated:
            {
                const auto& payload = std::get<AnimatedPayload>(cmd.data);
                const auto& spriteSheet = payload.sheet; 
                if (camera && cmd.cmd.layer != RenderLayer::HUD)
                {
                    auto locdst = camera->worldToScreen(spriteSheet.sprite.dst, winW, winH);
                    gfx->drawImageRegionById(spriteSheet.sprite.textureId, spriteSheet.sprite.src, locdst, spriteSheet.sprite.angle, spriteSheet.sprite.flip); 
                }
                else { gfx->drawImageRegionById(spriteSheet.sprite.textureId, spriteSheet.sprite.src, spriteSheet.sprite.dst, spriteSheet.sprite.angle, spriteSheet.sprite.flip); }
                break;
            }
            case RenderCommand::Type::Text:
            {
                const auto& payload = std::get<TextPayload>(cmd.data);
                const auto& text = payload.text; 
                if (camera && cmd.cmd.layer != RenderLayer::HUD)
                {
                    auto locdst = camera->worldToScreen(text.dst, winW, winH);
                    gfx->drawTextById(text.textId, locdst); 
                }
                else { gfx->drawTextById(text.textId, text.dst); }
 
                break;
            }
        }
    }
    cmdBuffer.clear();
}
