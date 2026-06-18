#ifndef GFXPORT_H
#define GFXPORT_H

#include "../../platform/WindowHandle.h"
#include "../../ports/GFXPort/GFXMath.h"
#include <string>

enum class FlipMode
{
    NONE,
    HORIZONTAL,
    VERTICAL,
};

struct IGFXPort
{
    virtual ~IGFXPort() = default;

    virtual bool init(WindowHandle handle, bool vsync) = 0;
    virtual void quitGFX() = 0;

    virtual bool beginFrame(Color color) = 0;
    virtual bool endFrame() = 0;

    virtual int loadImage(const std::string& path) = 0;
    virtual bool unloadImage(int id) = 0;

    virtual bool drawImageById(int id, Rect dst, float angle, FlipMode flip) = 0;
    virtual bool drawImageRegionById(int id, Rect src, Rect dst, float angle, FlipMode flip) = 0;
    
    virtual bool drawRect(Rect rect, Color c) = 0;
    virtual bool drawRectOutline(Rect rect, Color color) = 0;
    virtual bool drawLine(Vec2 a, Vec2 b, Color color) = 0;
};

#endif
