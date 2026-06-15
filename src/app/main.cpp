#include "../utils/Module.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>

#include "../core/EventDispatcher/EventDispatcher.h"
#include "../platform/IPlatform.h"

int main(int argc, char *argv[])
{
  try
  { 
    Utils::Module<IPlatform> platform; // Створення обгортки над класом з dll :: <Інтерфейс_обєкта>

    // Завантаження класу з dll :: функція отримує такі аргументи dllPath - шлях до dll :: createName - імя функції яка повертає вказівни на клас :: destroyName - імя функції яка знищує клас
    platform.load("SDL3Platform.dll", "getClass", "destroyClass"); // Завантаження класу з dll :: функція отримує такі аргументи dllPath - шлях до dll


    // Звернення до методів класу який був в dll :: створення під обєктів платформи
    platform->createBasePlatform();
    platform->createWindowPlatform();
    platform->createInputPlatform();
    platform->createAudioPlatform();

    // Ініціація платформи
    if (!platform->getBase()->init()) { throw std::runtime_error("failed to init base."); }
    if (!platform->getAudio()->initAudio()) { throw std::runtime_error("failed to init audio."); }
    
    std::string tag = "Music";
    int id1; 
    
    
    float vol = 1.0f;
    

    // Створення вікна Платформи
    platform->getWindow()->createWindow(800, 600, "SDL3");
 
    EventDispatcher dispatcher;
    
   

    puts("press A to create");
    dispatcher.subscribe(EventType::PG_Key_Down_A, [&](const Event& e)
    {
puts("you press A");
        id1 = platform->getAudio()->addAudioStream("music/Test.wav", tag); 
    });
    puts("press D to destroy");
    dispatcher.subscribe(EventType::PG_Key_Down_D, [&](const Event& e)
    {
puts("you press D");
        platform->getAudio()->stopAudioById(id1);
        platform->getAudio()->removeAudio(id1);
    });
 
    bool running = true;

    while (running)
    {
      platform.getInstance()->getBase()->update(16); // зупинка виконнання програми
      running = platform.getInstance()->getInput()->pollEvents(dispatcher); // обробробка івентів
      platform.getInstance()->getWindow()->renderFrame(); // рендер зображення вікна

      
    }

    platform->getWindow()->destroyWindow(); // знищення вікна
    platform->getBase()->shutdown(); // знищення бази платформи

  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    std::cin.get();
  }
  return 0;
}
