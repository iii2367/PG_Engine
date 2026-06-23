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

    if (!TTF_Init())
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        TTF_Quit();
        SDL_Log("Renderer error: %s", SDL_GetError());
        return false;
    }   

    if (vsync) 
    { 
        if (!SDL_SetRenderVSync(renderer, 1))
        {
            TTF_Quit();
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
            return false;
        }
    }
    return true;
}
bool GFXSDL3Adapter::init(WindowHandle handle, bool vsync, int driverIndex)
{
    if (renderer) { return false; }
    if (handle.type != TypeWindowHandle::SDL3) { return false; }

    window = static_cast<SDL_Window*>(handle.handle);
    if (!window) { return false; }

    if (!TTF_Init())
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        return false; 
    }

    renderer = SDL_CreateRenderer(window, SDL_GetRenderDriver(driverIndex)); 
    if (!renderer)
    {
        TTF_Quit();
        SDL_Log("Renderer error: %s", SDL_GetError());
        return false;
    }   

    if (vsync) 
    { 
        if (!SDL_SetRenderVSync(renderer, 1))
        {
            TTF_Quit();
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
    
    for (auto& [id, txt] : texts)
    {
        SDL_DestroyTexture(txt.texture);
    }

    texts.clear();

    for (auto& [id, font] : fonts)
    {
        TTF_CloseFont(font.font);
    }

    fonts.clear();

    if (TTF_WasInit()) { TTF_Quit(); }

    if (renderer) { SDL_DestroyRenderer(renderer); }
    renderer = nullptr;
    window = nullptr;
}
std::vector<RenderDriverInfo> GFXSDL3Adapter::getRenderDevices()
{
    std::vector<RenderDriverInfo> out;

    int count = SDL_GetNumRenderDrivers();
    for (int i = 0; i < count; i++)
    {
        const char* name = SDL_GetRenderDriver(i);
        if (!name) continue;

        out.push_back({ i, name });
    }

    return out;
}
std::any GFXSDL3Adapter::getContext()
{
    if (renderer) { return renderer; }
    return {};
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
    if (std::abs(angle) > 0.001f || flip != FlipMode::NONE)
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
    if (std::abs(angle) > 0.001f || flip != FlipMode::NONE)
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

/*============================================================================================*/

int GFXSDL3Adapter::loadFont(const std::string& path, int size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font) { return -1; }

    int id = nextFontId++;
    fonts[id] = { font };
    return id;
}
void GFXSDL3Adapter::unloadFont(int id)
{
    auto fit = fonts.find(id);

    if (fit == fonts.end()) { return; }

    for (auto it = texts.begin(); it != texts.end();)
    {
        if (it->second.fontId == id)
        {
            SDL_DestroyTexture(
                it->second.texture);

            it = texts.erase(it);
        }
        else
        {
            ++it;
        }
    }

    TTF_CloseFont(fit->second.font);
    fonts.erase(fit);
}
int GFXSDL3Adapter::createText(int fontId, const std::string& text, Color color)
{
    if (!renderer) { return -1; }
    auto fit = fonts.find(fontId);

    if (fit == fonts.end()) { return -1; }

    SDL_Color c
    {
        (Uint8)(color.r * 255),
        (Uint8)(color.g * 255),
        (Uint8)(color.b * 255),
        (Uint8)(color.a * 255)
    };

    SDL_Surface* surf =
        TTF_RenderText_Blended(
            fit->second.font,
            text.c_str(),
            text.size(),
            c);

    if (!surf)
        return -1;

    SDL_Texture* tex =
        SDL_CreateTextureFromSurface(
            renderer,
            surf);

    if (!tex)
    {
        SDL_DestroySurface(surf);
        return -1;
    }

    int id = nextTextId++;

    TextEntry entry;
    entry.texture = tex;
    entry.width = surf->w;
    entry.height = surf->h;
    entry.fontId = fontId;
    entry.text = text;
    entry.color = color;

    texts[id] = std::move(entry);

    SDL_DestroySurface(surf);

    return id;
}
bool GFXSDL3Adapter::drawTextById(int textId, Rect dst)
{
    if (!renderer) { return false; }
    auto it = texts.find(textId);

    if (it == texts.end()) { return false; }

    SDL_FRect r
    {
        dst.x,
        dst.y,
        dst.w > 0 ? dst.w : (float)it->second.width,
        dst.h > 0 ? dst.h : (float)it->second.height
    };

    return SDL_RenderTexture(renderer, it->second.texture, nullptr, &r);
}
bool GFXSDL3Adapter::updateText(int textId, const std::string& newText)
{
    auto tit = texts.find(textId);

    if (tit == texts.end()) { return false; }
    if (tit->second.text == newText) { return true; }

    auto fit = fonts.find(tit->second.fontId);

    if (fit == fonts.end()) { return false; }

    SDL_Color c
    {
        (Uint8)(tit->second.color.r * 255),
        (Uint8)(tit->second.color.g * 255),
        (Uint8)(tit->second.color.b * 255),
        (Uint8)(tit->second.color.a * 255)
    };

    SDL_Surface* surf = TTF_RenderText_Blended(fit->second.font, newText.c_str(), newText.size(), c);

    if (!surf) { return false; }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    if (!tex)
    {
        SDL_DestroySurface(surf);
        return false;
    }

    SDL_DestroyTexture(tit->second.texture);

    tit->second.texture = tex;
    tit->second.width = surf->w;
    tit->second.height = surf->h;
    tit->second.text = newText;

    SDL_DestroySurface(surf);
    return true;
}
bool GFXSDL3Adapter::unloadText(int id)
{
    auto it = texts.find(id);

    if (it == texts.end()) { return false; }

    SDL_DestroyTexture(it->second.texture);

    texts.erase(it);

    return true;
}


extern "C" __declspec(dllexport) IGFXPort* getClass() { return new GFXSDL3Adapter(); };
extern "C" __declspec(dllexport) void destroyClass(IGFXPort* ptr) { delete ptr; };
