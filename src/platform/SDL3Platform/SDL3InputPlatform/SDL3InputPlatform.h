#ifndef SDL3INPUTPLATFORM_H
#define SDL3INPUTPLATFORM_H

#include "../../../core/EventDispatcher/EventDispatcher.h"
#include "../../IInputPlatform.h"

#include <SDL3/SDL.h>
class SDL3InputPlatform : public IInputPlatform {
public:
  bool pollEvents(EventDispatcher &dispatcher) override;

  bool isKeyPressed(int keyCode) override;
  bool isMouseButtonPressed(int button) override;
  void getMousePosition(float &x, float &y) override;
};

#endif
