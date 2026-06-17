#ifndef GFXSDL3ADAPTER_H
#define GFXSDL3ADAPTER_H

#include "../../ports/GFXPort/GFXPort.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <vector>
#include <string>

class GFXSDL3Adapter : public IGFXPort
{
public:
    ~GFXSDL3Adapter() override;

    bool init(WindowHandle handle) override;
    void quitGFX() override;
    bool renderFrameBegin() override;
    bool renderFrameEnd() override;

    int addImage(const std::string& path, std::string& tag, Rect rect) override;
    bool removeImage(int id) override;

    bool drawImageById(int id, Vec4 dst) override;
    bool drawImageByTag(const std::string& tag, Rect dst) override;

    /*bool drawImageRegionById(int id, Rect src, Rect dst) override;
    bool drawImageRegionByTag(const std::string& tag, Rect src, Rect dst) override;

    bool drawRect(Rect r, Color c) override;
    bool clear(Color c) override;

    bool setImageAlphaById(int id, float alpha) override;
    bool setImageAlphaByTag(const std::string& tag, float alpha) override;

    bool setImageBlendModeById(int id, int blendMode) override;
    bool setImageBlendModeByTag(const std::string& tag, int blendMode) override;

    bool setImagePositionById(int id, Vec2 pos) override;
    bool setImagePositionByTag(const std::string& tag, Vec2 pos) override;

    bool setImageScaleById(int id, Vec2 scale) override;
    bool setImageScaleByTag(const std::string& tag, Vec2 scale) override;

    bool hideImageById(int id) override;
    bool hideImageByTag(const std::string& tag) override;

    bool showImageById(int id) override;
    bool showImageByTag(const std::string& tag) override;

    bool isImageVisibleById(int id) override;*/

private:
    struct ImageEntry
    {
        SDL_Texture* texture = nullptr;
        float alpha = 1.0f;
        SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;
        Vec2 position{0, 0};
        Vec2 scale{1, 1};
        bool visible = true;
        std::string tag;
    };

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int nextId = 1;

    std::unordered_map<int, ImageEntry> entries;
    std::unordered_map<std::string, std::vector<int>> tagMap;
    //std::unordered_map<int, ImageEntry> inRender;

    void bindTag(int id, const std::string& tag);
    void removeFromTag(int id, const std::string& tag);
    std::vector<int> getIdsByTag(const std::string& tag);
};

extern "C" __declspec(dllexport) IGFXPort* getClass();
extern "C" __declspec(dllexport) void destroyClass(IGFXPort* ptr);

#endif
