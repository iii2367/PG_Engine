#ifndef GFXSDL3ADAPTER_H
#define GFXSDL3ADAPTER_H

#include "../../ports/GFXPort/GFXPort.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>

#include <SDL3_ttf/SDL_ttf.h>

class GFXSDL3Adapter : public IGFXPort
{
public:
    ~GFXSDL3Adapter() override;

    bool init(WindowHandle handle, bool vsync) override;
    bool init(WindowHandle handle, bool vsync, int driverIndex) override;
    void quitGFX() override;
    std::vector<RenderDriverInfo> getRenderDevices() override;
    std::any getContext() override;

    bool beginFrame(Color color) override;
    bool endFrame() override;

    int loadImage(const std::string& path) override;
    bool unloadImage(int id) override;

    bool drawImageById(int id, Rect dst, float angle, FlipMode flip) override;
    bool drawImageRegionById(int id, Rect src, Rect dst, float angle, FlipMode flip) override;

    bool drawRect(Rect rect, Color c) override;
    bool drawRectOutline(Rect rect, Color color) override;
    bool drawLine(Vec2 a, Vec2 b, Color color) override;

    int loadFont(const std::string& path, int size) override;
    void unloadFont(int id) override;
    int createText(int fontId, const std::string& text, Color color) override;
    bool updateText(int textId, const std::string& text) override;
    bool unloadText(int textId) override;
    bool drawTextById(int textId, Rect dst) override;

private:
    struct ImageEntry
    {
        SDL_Texture* texture = nullptr; 
    };
    struct FontEntry
    {
        TTF_Font* font = nullptr;
    };
    struct TextEntry
    {
        SDL_Texture* texture = nullptr;
        int width = 0;
        int height = 0;

        int fontId = -1;

        std::string text;
        Color color;
    };


    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int nextId = 1;
    std::unordered_map<int, ImageEntry> entries;
    
    std::unordered_map<int, FontEntry> fonts;
    int nextFontId = 1;
    std::unordered_map<int, TextEntry> texts;
    int nextTextId = 1;

    SDL_FlipMode toSDLFlip(FlipMode flip);
};

extern "C" __declspec(dllexport) IGFXPort* getClass();
extern "C" __declspec(dllexport) void destroyClass(IGFXPort* ptr);

#endif
