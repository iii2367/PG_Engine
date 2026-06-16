#ifndef ENGINE
#define ENGINE

#include "../platform/IPlatform.h"
#include "../utils/Module.h"

enum class engineInfo {
  isPlatform,
  isBasePlatform,
  isAudioPlatform,
  isInputPlatform,
  isWindowPlatform,
  isEventDispatcher,
};

class Engine {
  EventDispatcher *eventDispatcher;
  Utils::Module<IPlatform> platform;

public:
  Engine() {}
  ~Engine() {}
  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;

  bool init(engineInfo info);

  IPlatform *getPlatform() const;
  IBasePlatform *getBasePlatform();
  IAudioPlatform *getAudioPlatform();
  IInputPlatform *getInputPlatform();
  IWindowPlatform *getWindowPlatform();
  EventDispatcher *getEventDispatcher();
};

#endif
