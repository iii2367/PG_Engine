#ifndef IINPUTPLATFORM_H
#define IINPUTPLATFORM_H

#include "../core/EventDispatcher/EventDispatcher.h"

struct pollStateStruct {
  bool w, a, s, d, q, r, e, f, c, x, z, Shift, ctrl, LMouseButton, RMouseButton;

  pollStateStruct() {
    w = a = s = d = q = r = e = f = c = x = z = Shift = ctrl = LMouseButton =
        RMouseButton = false;
  }
};

struct IInputPlatform {
  virtual ~IInputPlatform() = default;

  virtual void pollState(pollStateStruct &st) = 0;

  virtual bool pollEvents(EventDispatcher &dispatcher) = 0;

  virtual bool isKeyPressed(int keyCode) = 0;
  virtual bool isMouseButtonPressed(int button) = 0;
  virtual void getMousePosition(float &x, float &y) = 0;
};

#endif
