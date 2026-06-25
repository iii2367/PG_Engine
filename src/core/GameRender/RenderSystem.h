#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "../../ports/GFXPort/GFXPort.h"
#include "Camera.h"
#include "Sprite.h"
#include "PlayLoad.h"
#include "SpriteSheet.h"
#include <variant>

enum class RenderLayer
{
    Background,
    MediumShot,
    GameObjects,
    SpecialEffects,
    Foreground,
    HUD,
    Debug,
};

struct RenderCommand
{
    enum class Type
    {
        Sprite,
        Animated,
        Text
    };
    Type type;
    int entityId;                 

    RenderLayer layer;
    float z = 0.0f;        
};

class RenderSystem
{
public:
    explicit RenderSystem(IGFXPort& gfx);

    void submitSprite(RenderCommand cmd, Sprite sprite);
    void sublitAnimated(RenderCommand cmd, SpriteSheet spriteSheet);
    void submitText(RenderCommand cmd, Text text);
    
    void setCamera(Camera& cam);

    void present(float winW, float winH);

private:
    IGFXPort* gfx; 
    Camera* camera = nullptr;

    struct CommandBuffer
    {
        RenderCommand cmd;
        std::variant<SpritePayload, AnimatedPayload, TextPayload> data;
    };
    std::vector<CommandBuffer> cmdBuffer;
};
#endif
