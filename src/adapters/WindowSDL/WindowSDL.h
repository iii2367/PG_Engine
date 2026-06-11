#include "../../ports/WindowPort/WindowPort.h"

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
