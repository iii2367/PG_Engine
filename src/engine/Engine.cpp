#include "Engine.h"
#include <cstdint>

inline engineInfo operator|(engineInfo first, engineInfo next) {
  return static_cast<engineInfo>(static_cast<uint32_t>(first) |
                                 static_cast<uint32_t>(next));
}

inline bool operator&(engineInfo first, engineInfo next) {
  return (static_cast<uint32_t>(first) & static_cast<uint32_t>(next)) != 0;
}

bool Engine::init(engineInfo info) {
  if (info & engineInfo::isPlatform) {
    // platform init
    platform.load(
        "SDL3Platform.dll", "getClass",
        "destroyClass"); // Завантаження класу з dll :: функція отримує такі
  }
  if (info & engineInfo::isBasePlatform) {
    // base init
    platform->createBasePlatform();
    if (!platform->getBase()->init()) {
      return false;
    }
  }
  if (info & engineInfo::isWindowPlatform) {
    // window init
    platform->createWindowPlatform();
  }
  if (info & engineInfo::isAudioPlatform) {
    // audio init
    platform->createAudioPlatform();
    if (!platform->getAudio()->initAudio()) {
      return false;
    }
  }
  if (info & engineInfo::isInputPlatform) {
    // input init
    platform->createInputPlatform();
  }
  return true;
}

// on the bottom getters.

IPlatform *Engine::getPlatform() const {
  return platform.getInstance();
} // Возвращает платформ

IBasePlatform *Engine::getBasePlatform() {
  return platform->getBase();
} // Возвращает базовую платформу

IAudioPlatform *Engine::getAudioPlatform() {
  return platform->getAudio();
} // audio возвращает

IInputPlatform *Engine::getInputPlatform() {
  return platform->getInput();
} // input возвращает

IWindowPlatform *Engine::getWindowPlatform() {
  return platform->getWindow();
} // window возвращает

EventDispatcher *Engine::getEventDispatcher() {
  return eventDispatcher;
} // event возвращает
