#include "../engine/Engine.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
  try {
    Engine _Engine;
    engineInfo initInfo;
    _Engine.init(initInfo);
    EventDispatcher *dispatcher = _Engine.getEventDispatcher();

    IPlatform *platform = _Engine.getPlatform();
    platform->getWindow()->createWindow(800, 600, "SDL3");

    std::string tag = "Music";
    int id1;

    float vol = 1.0f;

    // Створення вікна Платформи
    dispatcher->subscribe(EventType::PG_Key_Down_P, [&](const Event &e) {
      puts("you press A");
      id1 = platform->getAudio()->addAudioStream("music/Test.wav", tag);
    });
    puts("press D to destroy");
    dispatcher->subscribe(EventType::PG_Key_Down_D, [&](const Event &e) {
      puts("you press D");
      platform->getAudio()->stopAudioById(id1);
      platform->getAudio()->removeAudio(id1);
    });

    bool running = true;

    while (running) {
      platform->getBase()->update(16); // зупинка виконнання програми
      running =
          platform->getInput()->pollEvents(*dispatcher); // обробробка івентів
      platform->getWindow()->renderFrame();              // render окна
    }

    platform->getWindow()->destroyWindow(); // знищення вікна
    platform->getBase()->shutdown();        // знищення бази платформи

  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    std::cin.get();
  }
  return 0;
}
