#include "WindowSDL.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

void SDL2WindowAdapter::CreateWindow(const WindowConfig &config) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return;
  }

  window = SDL_CreateWindow(config.title.c_str(), config.width, config.height,
                            SDL_WINDOW_RESIZABLE);
  if (!window) {
    SDL_Quit();
    return;
  }
}

void SDL2WindowAdapter::RenderFrame() {
  render = SDL_CreateRenderer(window, "render");
  if (!render) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
  }
  SDL_SetRenderDrawColor(render, 0, 0, 128, 255);
  SDL_RenderClear(render);

  // как я понял, тут отрисовка должна быть, судя по документации

  SDL_RenderPresent(render);
}

bool SDL2WindowAdapter::PollEvents() {
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

void SDL2WindowAdapter::CloseWindow() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
