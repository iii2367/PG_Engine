#ifndef ENGINE
#define ENGINE

#include "../utils/Module.h"
#include "IEngine.h"

class Engine : public IEngine{
  EventDispatcher* eventDispatcher = nullptr;
  Utils::Module<IPlatform> platform;
  Utils::Module<IGFXPort> gfx;

public:
  Engine() = default;
  ~Engine();
  
  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;
  Engine(Engine &&) = default;
  Engine &operator=(Engine&&) = default;

  bool init(EngineInitInfo info) override;

  IPlatform* getPlatform() const override;
  IGFXPort* getGFXAdapter() const override; 
  EventDispatcher* getEventDispatcher() const override;
};

extern "C" __declspec(dllexport) Engine* getClass();
extern "C" __declspec(dllexport) void destroyClass(Engine* ptr);
#endif
