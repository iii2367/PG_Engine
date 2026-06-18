#ifndef GFXSDL3ADAPTER_H
#define GFXSDL3ADAPTER_H

#include "../../ports/GFXPort/GFXPort.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>

class GFXSDL3Adapter : public IGFXPort
{
public:
    ~GFXSDL3Adapter() override;

    bool init(WindowHandle handle, bool vsync) override;
    void quitGFX() override;
    bool beginFrame(Color color) override;
    bool endFrame() override;

    int loadImage(const std::string& path) override;
    bool unloadImage(int id) override;

    bool drawImageById(int id, Rect dst, float angle) override;
    bool drawImageRegionById(int id, Rect src, Rect dst, float angle) override;
    bool drawRect(Rect rect, Color c) override;

private:
    struct ImageEntry
    {
        SDL_Texture* texture = nullptr; 
    };

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int nextId = 1;
    std::unordered_map<int, ImageEntry> entries;
};

extern "C" __declspec(dllexport) IGFXPort* getClass();
extern "C" __declspec(dllexport) void destroyClass(IGFXPort* ptr);

#endif
