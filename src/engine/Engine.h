#ifndef ENGINE
#define ENGINE

#include "../platform/IPlatform.h"
#include "../core/EventDispatcher/EventDispatcher.h"
#include "../utils/Module.h"

enum class EngineInitInfo {
  isBasePlatform =      1 << 0,
  isAudioPlatform =     1 << 1,
  isInputPlatform =     1 << 2,
  isWindowPlatform =    1 << 3,
  isEventDispatcher =   1 << 4,
};

inline EngineInitInfo operator|(EngineInitInfo first, EngineInitInfo next) {
  return static_cast<EngineInitInfo>(static_cast<uint32_t>(first) |
                                 static_cast<uint32_t>(next));
}
inline bool operator&(EngineInitInfo first, EngineInitInfo next) {
  return (static_cast<uint32_t>(first) & static_cast<uint32_t>(next)) != 0;
}

class Engine {
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
