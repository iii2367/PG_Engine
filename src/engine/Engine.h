#ifndef ENGINE
#define ENGINE

#include "../utils/Module.h"
#include "IEngine.h"

class Engine : public IEngine{
  EventDispatcher* eventDispatcher = nullptr;
  Utils::Module<IPlatform> platform;

public:
  Engine() = default;
  ~Engine();
  
  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;
  Engine(Engine &&) = default;
  Engine &operator=(Engine&&) = default;

  bool init(EngineInitInfo info);

  IPlatform* getPlatform() const;
  /*IBasePlatform* getBasePlatform() const;
  IAudioPlatform* getAudioPlatform() const;
  IInputPlatform* getInputPlatform() const;
  IWindowPlatform* getWindowPlatform() const;*/
  EventDispatcher* getEventDispatcher() const;
};

extern "C" __declspec(dllexport) Engine* getClass();
extern "C" __declspec(dllexport) void destroyClass(Engine* ptr);
#endif
