#include "GFXSDL3Adapter.h"
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

GFXSDL3Adapter::~GFXSDL3Adapter()
{
    quitGFX();
}

bool GFXSDL3Adapter::init(WindowHandle handle, bool vsync)
{
    if (renderer) { return false; }
    if (handle.type != TypeWindowHandle::SDL3) { return false; }

    window = static_cast<SDL_Window*>(handle.handle);
    if (!window) { return false; }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        SDL_Log("Renderer error: %s", SDL_GetError());
        return false;
    }   
    if (vsync) 
    { 
        if (!SDL_SetRenderVSync(renderer, 1))
        {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
            return false;
        }
    }
    return true;
}
void GFXSDL3Adapter::quitGFX()
{
    for (auto& [id, e] : entries)
    {
        SDL_DestroyTexture(e.texture);
    }
    
    entries.clear();

    if (renderer) { SDL_DestroyRenderer(renderer); }
    renderer = nullptr;
    window = nullptr;
}

/*============================================================================================*/

bool GFXSDL3Adapter::beginFrame(Color color) 
{
    if (!renderer) { return false; }

    SDL_SetRenderDrawColor(renderer, (Uint8)(color.r*255), (Uint8)(color.g*255), (Uint8)(color.b*255), (Uint8)(color.a*255));
    SDL_RenderClear(renderer); 
    return true;
}
bool GFXSDL3Adapter::endFrame() 
{
    if (!renderer) { return false; }

    SDL_RenderPresent(renderer);
    return true;
}

/*============================================================================================*/

int GFXSDL3Adapter::loadImage(const std::string& path) 
{
    if (!renderer) { return -1; }
    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (!tex) { return -1; }

    int id = nextId++;  
    entries[id] = {.texture = tex};
    return id;
}
bool GFXSDL3Adapter::unloadImage(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    if (it->second.texture) { SDL_DestroyTexture(it->second.texture); }
 
    entries.erase(it);
    return true;
}

/*============================================================================================*/

bool GFXSDL3Adapter::drawImageById(int id, Rect dst, float angle, FlipMode flip) 
{
    if (!renderer) { return false; }

    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    auto& img = it->second;
    if (!img.texture) { return false; }
 

    SDL_FRect rect{dst.x, dst.y, dst.w, dst.h};

    SDL_FlipMode sdlFlip = toSDLFlip(flip);
    if (angle != 0 || flip != FlipMode::NONE)
    {
        SDL_FPoint center{ rect.w * 0.5f, rect.h * 0.5f };
        return SDL_RenderTextureRotated(renderer, img.texture, nullptr, &rect, angle, &center, sdlFlip);
    }
    return SDL_RenderTexture(renderer, img.texture, nullptr, &rect);
}
bool GFXSDL3Adapter::drawImageRegionById(int id, Rect src, Rect dst, float angle, FlipMode flip)  
{
    if (!renderer) { return false; }

    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    auto& img = it->second;
    if (!img.texture) { return false; }

    SDL_FRect s{ src.x, src.y, src.w, src.h };
    SDL_FRect d{ dst.x, dst.y, dst.w, dst.h }; 

    SDL_FlipMode sdlFlip = toSDLFlip(flip);
    if (angle != 0 || flip != FlipMode::NONE)
    {
        SDL_FPoint center{ d.w * 0.5f, d.h * 0.5f };
        return SDL_RenderTextureRotated(renderer, img.texture, &s, &d, angle, &center, sdlFlip);
    }

    return SDL_RenderTexture(renderer, img.texture, &s, &d);
}

/*============================================================================================*/

bool GFXSDL3Adapter::drawRect(Rect rect, Color c)
{
    if (!renderer) { return false; }
    SDL_SetRenderDrawColor(renderer, (Uint8)(c.r * 255), (Uint8)(c.g * 255), (Uint8)(c.b * 255), (Uint8)(c.a * 255));
    SDL_FRect frect{rect.x, rect.y, rect.w, rect.h};
    return SDL_RenderFillRect(renderer, &frect);
}
bool GFXSDL3Adapter::drawLine(Vec2 a, Vec2 b, Color color)
{
    if (!renderer) { return false; }

    SDL_SetRenderDrawColor(renderer, (Uint8)(color.r * 255), (Uint8)(color.g * 255), (Uint8)(color.b * 255), (Uint8)(color.a * 255));
    return SDL_RenderLine(renderer, a.x, a.y, b.x, b.y);
}
bool GFXSDL3Adapter::drawRectOutline(Rect rect, Color color)
{
    if (!renderer) { return false; }

    SDL_SetRenderDrawColor(renderer, (Uint8)(color.r * 255), (Uint8)(color.g * 255), (Uint8)(color.b * 255), (Uint8)(color.a * 255));
    SDL_FRect r{ rect.x, rect.y, rect.w, rect.h};

    return SDL_RenderRect(renderer, &r);
}

/*============================================================================================*/

SDL_FlipMode GFXSDL3Adapter::toSDLFlip(FlipMode flip)
{
    switch (flip)
    {
        case FlipMode::HORIZONTAL: { return SDL_FLIP_HORIZONTAL; }

        case FlipMode::VERTICAL: { return SDL_FLIP_VERTICAL; }

        case FlipMode::NONE:
        default: { return SDL_FLIP_NONE; }
    }
}

extern "C" __declspec(dllexport) IGFXPort* getClass() { return new GFXSDL3Adapter(); };
extern "C" __declspec(dllexport) void destroyClass(IGFXPort* ptr) { delete ptr; };
