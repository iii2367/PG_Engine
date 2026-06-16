#include "Engine.h"

Engine::~Engine()
{
    if (platform.isLoaded()) { platform.unload(); }
}

bool Engine::init(EngineInitInfo info) 
{
  platform.load("SDL3Platform.dll", "getClass", "destroyClass"); 
  if (info & EngineInitInfo::isBasePlatform)
  {
    platform->createBasePlatform();
    if (!platform->getBase()->init())
    {
      return false;
    }
  }
  if (info & EngineInitInfo::isWindowPlatform)
  {
    platform->createWindowPlatform();
  }
  if (info & EngineInitInfo::isAudioPlatform) 
  {
    platform->createAudioPlatform();
    if (!platform->getAudio()->initAudio()) {
      return false;
    }
  }
  if (info & EngineInitInfo::isInputPlatform) 
  {
    platform->createInputPlatform();
  }
  if (info & EngineInitInfo::isEventDispatcher) { eventDispatcher = new EventDispatcher(); }
  return true;
}

IPlatform *Engine::getPlatform() const {
  return platform.getInstance();
} 
/*
IBasePlatform *Engine::getBasePlatform() const {
  return platform->getBase();
} 

IAudioPlatform *Engine::getAudioPlatform() const {
  return platform->getAudio();
} 

IInputPlatform *Engine::getInputPlatform() const {
  return platform->getInput();
} 

IWindowPlatform *Engine::getWindowPlatform() const {
  return platform->getWindow();
} 
*/
EventDispatcher *Engine::getEventDispatcher() const {
  return eventDispatcher;
}

extern "C" __declspec(dllexport) Engine* getClass() { return new Engine(); }
extern "C" __declspec(dllexport) void destroyClass(Engine* ptr) { delete ptr; }
