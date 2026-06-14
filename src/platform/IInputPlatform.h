#ifndef IINPUTPLATFORM_H
#define IINPUTPLATFORM_H

#include "../core/EventDispatcher/EventDispatcher.h"

struct IInputPlatform {
  virtual ~IInputPlatform() = default;

  virtual bool pollEvents(EventDispatcher &dispatcher) = 0;

  virtual bool isKeyPressed(int keyCode) = 0;
  virtual bool isMouseButtonPressed(int button) = 0;
  virtual void getMousePosition(float &x, float &y) = 0;
};

#endif
