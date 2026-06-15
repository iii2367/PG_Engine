#ifndef IWINDOWPLATFORM_H
#define IWINDOWPLATFORM_H

#include <string>

struct IWindowPlatform {
  virtual ~IWindowPlatform() = default;

  virtual bool createWindow(int width, int height, std::string title) = 0;
  virtual void renderFrame() = 0;
  virtual void destroyWindow() = 0;
  virtual void getWindowSize(int &w, int &h) = 0;
  virtual void setTitle(std::string title) = 0;
  virtual void resize(int width, int height) = 0;
  virtual void *getHandle() = 0;
};

#endif
