#include "WindowSDL3Adapter.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

void WindowSDL::createWindow(const WindowConfig &config) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return;
  }

  window = SDL_CreateWindow(config.title.c_str(), config.width, config.height,
                            SDL_WINDOW_RESIZABLE);

  render = SDL_CreateRenderer(window, nullptr);
  if (!window || !render) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
  }
}

void WindowSDL::RenderFrame() {
  SDL_SetRenderDrawColor(render, 0, 0, 128, 255);
  SDL_RenderClear(render);
  // как я понял, тут отрисовка должна быть, судя по документации
  SDL_RenderPresent(render);
}

bool WindowSDL::PollEvents() {
  SDL_Event event;
  isRunning = true;

  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT: {
      isRunning = false;
      return false;
    }
    }
  }
  return true;
}

void WindowSDL::CloseWindow() {
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

extern "C" __declspec(dllexport) IWindowPort *getClass() {
  return new WindowSDL();
}
extern "C" __declspec(dllexport) void destroyClass(IWindowPort *ptr) {
  delete ptr;
}
