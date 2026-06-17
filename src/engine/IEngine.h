#ifndef IENGINE_H
#define IENGINE_H

#include "../platform/IPlatform.h"
#include "../ports/GFXPort/GFXPort.h"
#include "../core/EventDispatcher/EventDispatcher.h"

enum class EngineInitInfo {
  isBasePlatform =      1 << 0,
  isAudioPlatform =     1 << 1,
  isInputPlatform =     1 << 2,
  isWindowPlatform =    1 << 3,
  isEventDispatcher =   1 << 4,
  isGFXAdapter =        1 << 5,
};

inline EngineInitInfo operator|(EngineInitInfo first, EngineInitInfo next) {
  return static_cast<EngineInitInfo>(static_cast<uint32_t>(first) |
                                 static_cast<uint32_t>(next));
}
inline bool operator&(EngineInitInfo first, EngineInitInfo next) {
  return (static_cast<uint32_t>(first) & static_cast<uint32_t>(next)) != 0;
}

struct IEngine
{
    virtual ~IEngine() = default;
    virtual bool init(EngineInitInfo info) = 0;
    virtual IPlatform* getPlatform() const = 0;
    virtual IGFXPort* getGFXAdapter() const = 0;
    virtual EventDispatcher* getEventDispatcher() const = 0;
};

#endif
