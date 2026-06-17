#ifndef GFXPORT_H
#define GFXPORT_H

#include "../../platform/WindowHandle.h"
#include "../../ports/GFXPort/GFXMath.h"
#include <string>


struct IGFXPort
{
    virtual ~IGFXPort() = default;

    virtual bool init(WindowHandle handle) = 0;
    virtual void quitGFX() = 0;
    virtual bool renderFrameBegin() = 0;
    virtual bool renderFrameEnd() = 0;

    virtual int addImage(const std::string& path, std::string& tag, Rect rect) = 0;
    virtual bool removeImage(int id) = 0;

    virtual bool drawImageById(int id, Vec4 dst) = 0;
    virtual bool drawImageByTag(const std::string& tag, Rect dst) = 0;

   /* virtual bool drawImageRegionById(int id, Rect src, Rect dst) = 0;
    virtual bool drawImageRegionByTag(const std::string& tag, Rect src, Rect dst) = 0;

    virtual bool drawRect(Rect r, Color c) = 0;

    virtual bool clear(Color c) = 0;

    virtual bool setImageAlphaById(int id, float alpha) = 0;
    virtual bool setImageAlphaByTag(const std::string& tag, float alpha) = 0;

    virtual bool setImageBlendModeById(int id, int blendMode) = 0;
    virtual bool setImageBlendModeByTag(const std::string& tag, int blendMode) = 0;

    virtual bool setImagePositionById(int id, Vec2 pos) = 0;
    virtual bool setImagePositionByTag(const std::string& tag, Vec2 pos) = 0;

    virtual bool setImageScaleById(int id, Vec2 scale) = 0;
    virtual bool setImageScaleByTag(const std::string& tag, Vec2 scale) = 0;

    virtual bool hideImageById(int id) = 0;
    virtual bool hideImageByTag(const std::string& tag) = 0;
    virtual bool showImageById(int id) = 0;
    virtual bool showImageByTag(const std::string& tag) = 0;

    virtual bool isImageVisibleById(int id) = 0;*/
};

#endif
