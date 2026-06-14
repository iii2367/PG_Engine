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
    int id1 = platform->getAudio()->addAudio("music/Test.wav", tag);
    int id2 = platform->getAudio()->addAudio("music/Test2.wav", tag);  
    int id3 = platform->getAudio()->addAudio("music/Test3.wav", tag);
    bool isPause = 0;
    float vol = 1.0f;

    // Створення вікна Платформи
    platform->getWindow()->createWindow(800, 600, "SDL3");
 
    // створення dispatcher для підписки подій (покищо невикористовується але потрібен)
    EventDispatcher dispatcher;
    std::cout << "Space = pause/resume\n" << "A = volume+\n" << "D = volume-\n"; 
    // Робимо підписку на подію KeyDown і якщо вона спрацьовує то викликається лямда функція
    dispatcher.subscribe(EventType::PG_Key_Down_SPACE, [&](const Event& e)
    {
        std::cout << "Pause/Resume" << std::endl; 
        if (!isPause) { isPause = 1; platform->getAudio()->pauseAudioAll(); } 
        else { isPause = 0; platform->getAudio()->resumeAudioAll(); }
    });
    dispatcher.subscribe(EventType::PG_Key_Down_D, [&](const Event& e)
    {
        std::cout << "DragonBorn volume+" << std::endl;
        if (vol < 10) { vol += 0.2f; std::cout << "Volume: "<< vol << std::endl; } else { vol = 10; puts("Volume = 10"); }
        platform->getAudio()->setVolumeById(id2,vol);
    });
    dispatcher.subscribe(EventType::PG_Key_Down_A, [&](const Event& e)
    {
        std::cout << "DragonBorn volume-" << std::endl;
        if (vol > 0) { vol -= 0.2f; std::cout << "Volume: "<< vol << std::endl; } else { vol = 0; puts("Volume = 0"); }
        platform->getAudio()->setVolumeById(id2,vol);
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
