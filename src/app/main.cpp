#include "../ports/WindowPort/WindowPort.h"
#include "../utils/Module.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>

#include "../core/EventDispatcher/EventDispatcher.h"
#include "../platform/IPlatform.h"

int main(int argc, char *argv[]) {
  try {
        // Завантаження потрібної dll
        Utils::Module<IPlatform> platform;
        platform.load("SDL3Platform.dll", "getClass", "destroyClass");
puts("1");
         
        // Запуск ініціації платформи
        if (!platform.getInstance()->getBase()->init()) { throw std::runtime_error("failed to init base"); }
puts("1.5");
        // Створення вікна платформи
        platform.getInstance()->getWindow()->createWindow(800, 600, "window");
puts("2");
        // створення dispatcher для підписки подій (покищо невикористовується але потрібен)
        EventDispatcher dispatcher;
        bool running = true;
puts("3");
        while (running)
        {
puts("4");
            platform.getInstance()->getBase()->update(); // зупинка виконнання програми
            running = platform.getInstance()->getInput()->pollEvents(dispatcher); // оброботка івентів
            platform.getInstance()->getWindow()->renderFrame(); // рендер зображення вікна

        }
puts("5");
        platform.getInstance()->getWindow()->destroyWindow(); // знищення вікна
        platform.getInstance()->getBase()->shutdown(); // знищення бази платформи
puts("6");

  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    std::cin.get();
  }
  return 0;
}
