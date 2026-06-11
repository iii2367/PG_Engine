#include "../ports/WindowPort/WindowPort.h"
#include "../utils/ModuleDLL.h"
#include <cstdio>

int main(int argc, char *argv[]) {

  puts("Utils");
  Utils::Module<IWindowPort> win;
  win.load("WindowSDL/WindowSDL.dll", "getClass", "destroyClass");
  puts("Config");
  WindowConfig wConfig;
  wConfig.height = 640;
  wConfig.width = 800;
  wConfig.title = "SDL3";
  puts("main program");
  win.getInstance()->createWindow(wConfig);
  puts("cycle");
  while (win.getInstance()->PollEvents()) {
    win.getInstance()->RenderFrame();
  }
  puts("CloseWindow");
  win.getInstance()->CloseWindow();
  win.unload();
}
