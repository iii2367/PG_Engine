#include "imguiInterface.h"

void ImGui_Interface::IMGUI_createContext() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
}

ImGuiIO &ImGui_Interface::IMGUI_initIO() {
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  return io;
}

void ImGui_Interface::IMGUI_pickColor() { ImGui::StyleColorsDark(); }

void ImGui_Interface::IMGUI_InitAllSDL3() {
  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);
}

void ImGui_Interface::IMGUI_pollEvent(SDL_Event &event) {
  ImGui_ImplSDL3_ProcessEvent(&event);
}

void ImGui_Interface::IMGUI_NewFrame() {
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void ImGui_Interface::IMGUI_Begin() {
  ImGui::Begin("ImGui Window", nullptr,
               ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize);
}

void ImGui_Interface::IMGUI_End() { ImGui::End(); }

void ImGui_Interface::IMGUI_Render() { ImGui::Render(); }

void ImGui_Interface::IMGUI_RenderDrawData() {
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

ImGui_Interface::~ImGui_Interface() {
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}
