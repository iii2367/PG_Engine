#include "SDL3WindowPlatform.h"
#include <SDL3/SDL_video.h>

bool SDL3WindowPlatform::createWindow(int width, int height,
                                      std::string title) {
  window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);

  render = SDL_CreateRenderer(window, nullptr);
  if (!window || !render) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return false;
  }
  return true;
}

void SDL3WindowPlatform::destroyWindow() {
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
}

void SDL3WindowPlatform::renderFrame() {
  SDL_SetRenderDrawColor(render, 128, 128, 128, 255);
  SDL_RenderClear(render);
  SDL_RenderPresent(render);
}

void SDL3WindowPlatform::setTitle(std::string title) {
  if (window) {
    SDL_SetWindowTitle(window, title.c_str());
  }
}

void SDL3WindowPlatform::resize(int width, int height) {
  if (window) {
    SDL_SetWindowSize(window, width, height);
  }
}

void SDL3WindowPlatform::getWindowSize(int &w, int &h) {
  if (window) {
    SDL_GetWindowSize(window, &w, &h);
  }
}

void *SDL3WindowPlatform::getHandle() {
  /*#if defined(_WIN32)
    return (void *)SDL_GetProperty(SDL_GetWindowProperties(window),
                                   SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
  #elif defined(linux)
    return (void *)SDL_GetProperty(SDL_GetWindowProperties(window),
                                   SDL_PROP_WINDOW_X11_WINDOW_NUMBER, nullptr);
  #elif defined(APPLE)
    return (void *)SDL_GetProperty(SDL_GetWindowProperties(window),
                                   SDL_PROP_WINDOW_COCOA_WINDOW_POINTER,
  nullptr); #endif
  */
}
