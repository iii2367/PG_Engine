#pragma once

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <string>

class ImGui_Interface {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

public:
  ImGui_Interface(SDL_Window *window, SDL_Renderer *renderer)
      : window(window), renderer(renderer) {}

  ~ImGui_Interface();
  void IMGUI_createContext() const;
  ImGuiIO &IMGUI_initIO() const;
  void IMGUI_pickColor() const;
  void IMGUI_InitAllSDL3() const;
  void IMGUI_pollEvent(SDL_Event &event) const;

  void IMGUI_NewFrame() const;
  void IMGUI_Begin(const std::string &winName, ImGuiWindowFlags &flags) const;

  void IMGUI_End() const;
  void IMGUI_Render() const;
  void IMGUI_RenderDrawData() const;
};
