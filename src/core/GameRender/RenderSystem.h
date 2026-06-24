#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "../../ports/GFXPort/GFXPort.h"
#include "Camera.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include <unordered_map>

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
    explicit RenderSystem(IGFXPort& gfx) : gfx(&gfx) {}

    void submit(int id, const RenderCommand& cmd);

    void drawSprite(int id);
    void drawAnimated(int id);
    void drawText(int id);
    
    void setCamera(Camera& camera);

    void present(float w, float h);

private:
    IGFXPort* gfx;
    std::unordered_map<int, Sprite> sprites;
    std::unordered_map<int, AnimatedSprite*> animated;

    Camera* camera;

    std::vector<RenderCommand> commandBuffer;
};
#endif
