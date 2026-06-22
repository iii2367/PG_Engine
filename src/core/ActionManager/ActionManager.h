#ifndef ACTIONMANAGER
#define ACTIONMANAGER

#include "../../platform/IInputPlatform.h"
#include "../Key/InputKey.h"
#include "InputAction.h"
#include <string>
#include <unordered_map>

class ActionManager {
public:
  std::unordered_map<std::string, InputAction> actions;
  bool IsActive(const std::string &actionName, IInputPlatform *platform);
};

#endif
