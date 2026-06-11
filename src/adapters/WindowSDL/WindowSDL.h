#ifndef WINDOWSDL
#define WINDOWSDL

#include "../../ports/WindowPort/WindowPort.h"
#include <SDL3/SDL.h>

class SDL2WindowAdapter : public IWindowPort {
private:
  SDL_Window *window = nullptr;
  SDL_Renderer *render = nullptr;
  bool isRunning = false;

public:
  void CreateWindow(const WindowConfig &config) override;
  void RenderFrame() override;
  bool PollEvents() override;
  void CloseWindow() override;
};

#endif // WINDOWSDL
