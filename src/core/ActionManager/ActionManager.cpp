#include "ActionManager.h"
#include "InputAction.h"
#include <string>

bool ActionManager::IsActive(const std::string &actionName,
                             IInputPlatform *platform) {
  auto action = actions.find(actionName);
  if (action == actions.end())
    return false;
  for (const auto &key : action->second.bindings) {
    if (platform->getKeyState(key))
      return true;
  }
  return false;
}
