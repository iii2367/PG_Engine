#ifndef SDL3WINDOWPLATFORM_H
#define SDL3WINDOWPLATFORM_H

#include "../../IWindowPlatform.h"

#include <SDL3/SDL.h>

class SDL3WindowPlatform : public IWindowPlatform {

  bool isHaveWindow = false;

public:
  SDL_Window *window = nullptr;
  SDL_Renderer *render = nullptr;

  bool createWindow(const WindowInfo &info) override;
  void destroyWindow() override;
  bool renderFrame() override;
  void getWindowSize(int &w, int &h) override;
  void setTitle(std::string title) override;
  void resize(int width, int height) override;
  WindowHandle getWindowHandle() override;

  void setWindowSize(int x, int y) override;
  const char *getTitle() override;
  void setFullScreen(bool enabled) override;
  bool isFullScreen() override;
  void show() override;
  void hide() override;
  bool isVisible() override;
  void setCursorVisible(bool visible) override;
  bool isCursorVisible() override;
  void setCursorPosition(float x, float y) override;
  void getCursorPosition(float &x, float &y) override;
};

#endif
