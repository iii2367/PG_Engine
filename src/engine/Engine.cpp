#include "Engine.h"
#include "IEngine.h"

Engine::~Engine()
{
    if (gfx.isLoaded()) { gfx.unload(); }
    if (platform.isLoaded()) { platform.unload(); }
}

bool Engine::init(EngineInitInfo info) 
{   
    if (!platform.load("SDL3Platform.dll", "getClass", "destroyClass")) { return false; }
    if (info & EngineInitInfo::isBasePlatform) { platform->createBasePlatform(); }
    if (info & EngineInitInfo::isWindowPlatform) { platform->createWindowPlatform(); }
    if (info & EngineInitInfo::isInputPlatform) { platform->createInputPlatform(); }
    if (info & EngineInitInfo::isAudioPlatform) { platform->createAudioPlatform(); }

    if (info & EngineInitInfo::isEventDispatcher) { eventDispatcher = new EventDispatcher(); }

    if (info & EngineInitInfo::isGFXAdapter) { if(!gfx.load("GFXSDL3Adapter.dll", "getClass", "destroyClass")) { return false; } }
  return true;
}

IPlatform *Engine::getPlatform() const { return platform.getInstance(); } 
IGFXPort* Engine::getGFXAdapter() const { return gfx.getInstance(); }
EventDispatcher *Engine::getEventDispatcher() const { return eventDispatcher; }

extern "C" __declspec(dllexport) Engine* getClass() { return new Engine(); }
extern "C" __declspec(dllexport) void destroyClass(Engine* ptr) { delete ptr; }
