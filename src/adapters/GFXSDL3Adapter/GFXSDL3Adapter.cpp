#include "GFXSDL3Adapter.h"
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

GFXSDL3Adapter::~GFXSDL3Adapter()
{
    quitGFX();
}

bool GFXSDL3Adapter::init(WindowHandle handle)
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
    return true;
}
void GFXSDL3Adapter::quitGFX()
{
    for (auto& [id, e] : entries)
    {
        SDL_DestroyTexture(e.texture);
    }
    
    entries.clear();
    tagMap.clear();

    if (renderer) { SDL_DestroyRenderer(renderer); }
    renderer = nullptr;
    window = nullptr;
}
bool GFXSDL3Adapter::renderFrameBegin() 
{
    if (!renderer) { return false; }

    SDL_SetRenderDrawColor(renderer, 0, 255, 50, 100);
    SDL_RenderClear(renderer); 
    //Рендер
    //drawImageById(nextId-1, {400,400,50,50});

    //SDL_RenderPresent(renderer);
    return true;
}
bool GFXSDL3Adapter::renderFrameEnd() 
{
    if (!renderer) { return false; }

    //SDL_SetRenderDrawColor(renderer, 0, 255, 50, 100);
    //SDL_RenderClear(renderer); 
    //Рендер
    SDL_RenderPresent(renderer);
    return true;
}

int GFXSDL3Adapter::addImage(const std::string& path, std::string& tag, Rect rect) 
{
    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (!tex) { return -1; }

    int id = nextId++; 

    entries[id] = {.texture=tex, .position={rect.x, rect.y}, .scale={rect.w, rect.h}, .tag=tag};
    bindTag(id, tag);

    return id;
}
bool GFXSDL3Adapter::removeImage(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    if (it->second.texture) { SDL_DestroyTexture(it->second.texture); }

    removeFromTag(id, it->second.tag);
    entries.erase(it);

    return true;
}

bool GFXSDL3Adapter::drawImageById(int id, Vec4 dst) 
{
    if (!renderer) { return false; }
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    auto& img = it->second;
    if (!img.texture || !img.visible) { return false; }

    SDL_SetTextureAlphaMod(img.texture, (Uint8)(img.alpha * 255));
    SDL_SetTextureBlendMode(img.texture, img.blendMode);

    SDL_FRect rect;
    rect.x = dst.x;
    rect.y = dst.y;
    rect.w = dst.z;
    rect.h = dst.w;

    return SDL_RenderTexture(renderer, img.texture, nullptr, &rect);
}
bool GFXSDL3Adapter::drawImageByTag(const std::string& tag, Rect dst) 
{
    if (!renderer) { return false; }
    bool ok = true;

    for (int id : getIdsByTag(tag))
    {
        ok &= drawImageById(id, Vec4(dst.x, dst.y, dst.w, dst.h));
    }

    return ok;
}
/*
bool GFXSDL3Adapter::drawImageRegionById(int id, Rect src, Rect dst)  // помилка
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    auto& img = it->second.image;
    if (!img.texture || !img.visible) { return false; }

    SDL_Rect s{ (int)src.x, (int)src.y, (int)src.w, (int)src.h };
    SDL_FRect d{ dst.x, dst.y, dst.w, dst.h };

    SDL_SetTextureAlphaMod(img.texture, (Uint8)(img.alpha * 255));
    SDL_SetTextureBlendMode(img.texture, img.blendMode);

    //SDL_RenderTexture(renderer, img.texture, &s, &d);
}
bool GFXSDL3Adapter::drawImageRegionByTag(const std::string& tag, Rect src, Rect dst) {}

bool GFXSDL3Adapter::drawRect(Rect r, Color c) 
{
    SDL_SetRenderDrawColor(renderer,
        (Uint8)(c.r * 255),
        (Uint8)(c.g * 255),
        (Uint8)(c.b * 255),
        (Uint8)(c.a * 255));

    SDL_FRect rect{r.x, r.y, r.w, r.h};
    return SDL_RenderFillRect(renderer, &rect);
}
bool GFXSDL3Adapter::clear(Color c) 
{
    SDL_SetRenderDrawColor(renderer,
        (Uint8)(c.r * 255),
        (Uint8)(c.g * 255),
        (Uint8)(c.b * 255),
        (Uint8)(c.a * 255));

    return SDL_RenderClear(renderer);
}

bool GFXSDL3Adapter::setImageAlphaById(int id, float alpha) {}
bool GFXSDL3Adapter::setImageAlphaByTag(const std::string& tag, float alpha) {}

bool GFXSDL3Adapter::setImageBlendModeById(int id, int blendMode) {}
bool GFXSDL3Adapter::setImageBlendModeByTag(const std::string& tag, int blendMode) {}

bool GFXSDL3Adapter::setImagePositionById(int id, Vec2 pos) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    it->second.image.position = pos;
    return true;
}
bool GFXSDL3Adapter::setImagePositionByTag(const std::string& tag, Vec2 pos) {}

bool GFXSDL3Adapter::setImageScaleById(int id, Vec2 scale) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    it->second.image.scale = scale;
    return true;
}
bool GFXSDL3Adapter::setImageScaleByTag(const std::string& tag, Vec2 scale) {}

bool GFXSDL3Adapter::hideImageById(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    it->second.image.visible = false;
    return true;
}
bool GFXSDL3Adapter::hideImageByTag(const std::string& tag) {}

bool GFXSDL3Adapter::showImageById(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) return false;

    it->second.image.visible = true;
    return true; 
}
bool GFXSDL3Adapter::showImageByTag(const std::string& tag) {}

bool GFXSDL3Adapter::isImageVisibleById(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) return false;

    return it->second.image.visible;
}
*/
void GFXSDL3Adapter::bindTag(int id, const std::string& tag)
{
    tagMap[tag].push_back(id);
}
void GFXSDL3Adapter::removeFromTag(int id, const std::string& tag)
{
    auto& vec = tagMap[tag];
    vec.erase(std::remove(vec.begin(), vec.end(), id), vec.end());
}
std::vector<int> GFXSDL3Adapter::getIdsByTag(const std::string& tag)
{
    if (!tagMap.count(tag)) { return {}; }
    return tagMap[tag];
}

extern "C" __declspec(dllexport) IGFXPort* getClass() { return new GFXSDL3Adapter(); };
extern "C" __declspec(dllexport) void destroyClass(IGFXPort* ptr) { delete ptr; };
