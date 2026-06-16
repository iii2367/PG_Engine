#ifndef IWINDOWPLATFORM_H
#define IWINDOWPLATFORM_H

#include <string>
#include "WindowHandle.h"

struct WindowInfo
{
    int width{800};
    int height{600};
    std::string title{"Window"};

    bool enableRender{false};   
    bool resizable{false};      
    bool fullscreen{false};        
    bool decorated{true};
};

struct IWindowPlatform {
  virtual ~IWindowPlatform() = default;

  virtual bool createWindow(const WindowInfo& info) = 0;
  virtual bool renderFrame() = 0;
  virtual void destroyWindow() = 0;
  virtual void getWindowSize(int &w, int &h) = 0;
  virtual void setTitle(std::string title) = 0;
  virtual void resize(int width, int height) = 0;
  virtual WindowHandle getWindowHandle() = 0;
};

#endif
