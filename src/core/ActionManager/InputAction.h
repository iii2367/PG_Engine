#ifndef INPUTACTION
#define INPUTACTION

#include "../Key/InputKey.h"
#include <string>
#include <vector>

struct InputAction {

  std::string name;
  std::vector<InputKey> bindings;
};

#endif
