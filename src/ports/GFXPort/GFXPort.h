#ifndef GFXPORT_H
#define GFXPORT_H

#include "../../platform/WindowHandle.h"
#include "../../core/Math/Math.h"
#include <string>

enum class FlipMode
{
    NONE,
    HORIZONTAL,
    VERTICAL,
};

struct RenderDriverInfo
{
    int index;
    std::string name;
};

struct IGFXPort
{
    virtual ~IGFXPort() = default;

    virtual bool init(WindowHandle handle, bool vsync) = 0;
    virtual bool init(WindowHandle handle, bool vsync, int driverIndex) = 0;
    virtual void quitGFX() = 0;
    virtual std::vector<RenderDriverInfo> getRenderDevices() = 0;

    virtual bool beginFrame(Color color) = 0;
    virtual bool endFrame() = 0;

    virtual int loadImage(const std::string& path) = 0;
    virtual bool unloadImage(int id) = 0;

    virtual bool drawImageById(int id, Rect dst, float angle, FlipMode flip) = 0;
    virtual bool drawImageRegionById(int id, Rect src, Rect dst, float angle, FlipMode flip) = 0;
    
    virtual bool drawRect(Rect rect, Color c) = 0;
    virtual bool drawRectOutline(Rect rect, Color color) = 0;
    virtual bool drawLine(Vec2 a, Vec2 b, Color color) = 0;

    virtual int loadFont(const std::string& path, int size) = 0;
    virtual void unloadFont(int id) = 0;
    virtual int createText(int fontId, const std::string& text, Color color) = 0;
    virtual bool updateText(int textId, const std::string& text) = 0;
    virtual bool unloadText(int textId) = 0;
    virtual bool drawTextById(int textId, Rect dst) = 0;
};

#endif
