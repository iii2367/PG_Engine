#include "WindowSDL.h"
#include <SDL3/SDL.h>
void SDL2WindowAdapter::CreateWindow(const WindowConfig &config) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    return;
  }

  SDL_Surface *Surface = nullptr;

  window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, config.width,
                            config.height, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    return;
  }

  Surface = SDL_GetWindowSurface(window);
  SDL_FillRect(Surface, nullptr, SDL_MapRGB(Surface->format, 0, 255, 0));
  SDL_UpdateWindowSurface(window);
}

void SDL2WindowAdapter::RenderFrame() {
  SDL_SetRenderDrawColor(render, 20, 40, 80, 255);
  SDL_RenderClear(render);

  SDL_Rect rect = {350, 250, 100, 100};
  SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
  SDL_RenderFillRect(render, &rect);

  SDL_RenderPresent(render);
}

bool SDL2WindowAdapter::PollEvents() {

  SDL_Event event;

  isRunning = true;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    return false;
    break;
  }

  return true;
}

void SDL2WindowAdapter::CloseWindow() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
