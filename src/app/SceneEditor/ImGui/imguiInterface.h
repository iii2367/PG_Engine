#pragma once

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

class ImGui_Interface {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

public:
  ImGui_Interface(SDL_Window *window, SDL_Renderer *renderer)
      : window(window), renderer(renderer) {}

  ~ImGui_Interface();
  void IMGUI_createContext();
  ImGuiIO &IMGUI_initIO();
  void IMGUI_pickColor();
  void IMGUI_InitAllSDL3();
  void IMGUI_pollEvent(SDL_Event &event);

  void IMGUI_NewFrame();
  void IMGUI_Begin();
  void IMGUI_End();
  void IMGUI_Render();
  void IMGUI_RenderDrawData();
};
