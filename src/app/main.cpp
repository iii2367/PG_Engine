#include "../adapters/WindowSDL/WindowSDL.h"
#include <iostream>

int main() {
  WindowConfig wConfig;
  wConfig.height = 640;
  wConfig.width = 800;
  wConfig.title = "SDL3";

  SDL2WindowAdapter SDL3;

  SDL3.CreateWindow(wConfig);

  while (SDL3.PollEvents()) {
    SDL3.RenderFrame();
  }

  SDL3.CloseWindow();
}
