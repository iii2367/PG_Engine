#include "SDL3WindowPlatform.h"
#include <SDL3/SDL_platform.h>
#include <SDL3/SDL_video.h>

bool SDL3WindowPlatform::createWindow(const WindowInfo& info) {
    if (window || render) { return false; }
    
    Uint32 flags = 0;
    if (info.resizable) { flags |= SDL_WINDOW_RESIZABLE; }
    if (info.fullscreen) { flags |= SDL_WINDOW_FULLSCREEN; }
    if (!info.decorated) { flags |= SDL_WINDOW_BORDERLESS; }
    
    window = SDL_CreateWindow(info.title.c_str(), info.width, info.height, flags);
    if (!window) { SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError()); return false; }
    
    if (info.enableRender) { 
        render = SDL_CreateRenderer(window, nullptr); 
        if (!render) { SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
            SDL_DestroyWindow(window);
            window = nullptr;
            return false;
        }
    }
  return true;
}

void SDL3WindowPlatform::destroyWindow() {
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
}

bool SDL3WindowPlatform::renderFrame() {
  if (!render) { return false; }
  SDL_SetRenderDrawColor(render, 128, 128, 128, 255);
  SDL_RenderClear(render);
  SDL_RenderPresent(render);
  return true;
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

WindowHandle SDL3WindowPlatform::getWindowHandle() {
    WindowHandle wh{};
    wh.type = TypeWindowHandle::SDL3;
    wh.handle = window;
    getWindowSize(wh.width, wh.height);
    return wh;
}
