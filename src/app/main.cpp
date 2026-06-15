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
    int id4 = platform->getAudio()->addAudio("music/Test4.wav", tag);
    int id5 = platform->getAudio()->addAudio("music/Test5.wav", tag);
    float vol = 1.0f;
    platform->getAudio()->stopAudioAll();

    // Створення вікна Платформи
    platform->getWindow()->createWindow(800, 600, "SDL3");
 
    // створення dispatcher для підписки подій (покищо невикористовується але потрібен)
    EventDispatcher dispatcher;
    
    puts("press Q to play next");
    int curId = id1;
    platform->getAudio()->restartAudioById(id1);
    dispatcher.subscribe(EventType::PG_Key_Down_Q, [&](const Event& e)
    {
        if (curId == id1) 
        { 
            curId = id2;
            platform->getAudio()->stopAudioById(id1);
            platform->getAudio()->restartAudioById(id2);
        }
        else if (curId == id2) 
        { 
            curId = id3;
            platform->getAudio()->stopAudioById(id2);
            platform->getAudio()->restartAudioById(id3);
        }
        else if (curId == id3) 
        { 
            curId = id4;
            platform->getAudio()->stopAudioById(id3);
            platform->getAudio()->restartAudioById(id4);
        }
        else if (curId == id4) 
        { 
            curId = id5;
            platform->getAudio()->stopAudioById(id4);
            platform->getAudio()->restartAudioById(id5);
        }
        else if (curId == id5) 
        { 
            curId = id1;
            platform->getAudio()->stopAudioById(id5);
            platform->getAudio()->restartAudioById(id1);
        }
    });
    
    puts("press W to go");
    dispatcher.subscribe(EventType::PG_Key_Down_W, [&](const Event& e)
    {
        if (platform->getAudio()->isFinishedById(id5))
        {
            platform->getAudio()->restartAudioById(id5);
        }
    });
    puts("press F to shoot");
    dispatcher.subscribe(EventType::PG_Key_Down_F, [&](const Event& e)
    {
        if (platform->getAudio()->isFinishedById(id4))
        {
            platform->getAudio()->restartAudioById(id4);
        }
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
