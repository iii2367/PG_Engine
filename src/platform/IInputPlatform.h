#ifndef IINPUTPLATFORM_H
#define IINPUTPLATFORM_H

#include "../core/EventDispatcher/EventDispatcher.h"

struct pollStateStruct {
  bool W = false;
  bool A = false;
  bool S = false;
  bool D = false;
  bool Q = false;
  bool R = false; 
  bool E = false; 
  bool F = false; 
  bool C = false;
  bool X = false; 
  bool Z = false;
  bool LShift = false; 
  bool LCtrl = false; 
  bool LMouseButton = false;
  bool RMouseButton = false;


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
