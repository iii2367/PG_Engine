#include "../ports/WindowPort/WindowPort.h"
#include "../utils/Module.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
  try {
    puts("Utils");
    Utils::Module<IWindowPort> win;
    puts("load dll");
    win.load("WindowSDL3Adapter.dll", "getClass", "destroyClass");
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

  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    std::cin.get();
  }
  return 0;
}
