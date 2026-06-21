#include "Engine.h"

Engine::~Engine()
{
    if (gfx.isLoaded()) { gfx.unload(); }
    if (platform.isLoaded()) { platform.unload(); }
}

bool Engine::init() 
{   
    if (!platform.load("SDL3Platform.dll", "getClass", "destroyClass")) { return false; }
    if (!gfx.load("GFXSDL3Adapter.dll", "getClass", "destroyClass")) { return false; } 
    if (eventDispatcher) { return false; }
    eventDispatcher = new EventDispatcher(); 

  return true;
}

IPlatform *Engine::getPlatform() const { return platform.get(); } 
IGFXPort* Engine::getGFXAdapter() const { return gfx.get(); }
EventDispatcher *Engine::getEventDispatcher() const { return eventDispatcher; }

extern "C" __declspec(dllexport) Engine* getClass() { return new Engine(); }
extern "C" __declspec(dllexport) void destroyClass(Engine* ptr) { delete ptr; }
