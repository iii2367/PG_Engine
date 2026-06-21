#ifndef IENGINE_H
#define IENGINE_H

#include "../platform/IPlatform.h"
#include "../ports/GFXPort/GFXPort.h"
#include "../core/EventDispatcher/EventDispatcher.h"

struct IEngine
{
    virtual ~IEngine() = default;
    virtual bool init() = 0;
    virtual IPlatform* getPlatform() const = 0;
    virtual IGFXPort* getGFXAdapter() const = 0;
    virtual EventDispatcher* getEventDispatcher() const = 0;
};

#endif
