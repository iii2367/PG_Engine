#include "../engine/Engine.h"
#include "Module.h"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include "../core/ActionManager/ActionManager.h"
#include "../core/ActionManager/InputAction.h"

int main(int argc, char *argv[]) {
  try {
    Utils::Module<Engine> engine;
    engine.load("Engine.dll", "getClass", "destroyClass");
    engine->init();


    auto platform = engine->getPlatform();
    platform->init();
    auto window = engine->getPlatform()->getWindow();
    auto input = engine->getPlatform()->getInput();
    auto audio = engine->getPlatform()->getAudio();
    auto eventDispatcher = engine->getEventDispatcher();
    auto gfx = engine->getGFXAdapter();

    audio->initAudio();

    WindowInfo winInfo{};
    winInfo.decorated = 1;
    winInfo.resizable = 1;
    window->createWindow(winInfo);

    std::string audioTag = "Music";
    auto id1 = audio->addAudioStream("music/TestStream1.wav", audioTag);
    audio->loopAudioById(id1);

    auto handle = window->getWindowHandle();
    if (!gfx->init(handle, true)) {
      throw std::runtime_error("failed to init gfx");
    }
    Vec4 dst{400, 300, 200, 200};
    int imId = gfx->loadImage("image/image1.png");
    std::cout << imId << '\n';
    int alf = gfx->loadImage("image/Alf.png");

    auto deviceCount = gfx->getRenderDevices();
    for (auto device : deviceCount) {
      std::cout << device.index << '\t' << device.name << '\n';
    }

    int fontId = gfx->loadFont("font/ChelseaMarket.ttf", 22);
    int helloText = gfx->createText(fontId, "Hello World", {0, 0, 0, 0});

    
    std::atomic<bool> runningRender{true};
    float an = 0.5;
std::atomic<int> fps{0};
    std::thread renderThread([&] {
using clock = std::chrono::high_resolution_clock;
auto lastTime = clock::now();
int frameCount = 0;
int ft = gfx->createText(fontId, "FPS: ", {0, 0, 0, 0});


      while (runningRender) {
frameCount++;

        // ===== FPS CALC =====
        auto now = clock::now();
        std::chrono::duration<float> delta = now - lastTime;

        if (delta.count() >= 1.0f) {
            fps = frameCount;   // запис FPS
            frameCount = 0;
            lastTime = now;

            // (опціонально) вивід в консоль
            std::cout << "FPS: " << fps.load() << std::endl;
            gfx->updateText(ft, "FPS: " + std::to_string(fps.load()));
        }



        an += 1;
        gfx->beginFrame({1.0f, 1.0f, 1.0f, 1.0f});
        // gfx->drawRect({50,50,50,50}, {0.0f,1.0f,1.0f,1.0f});
          gfx->drawImageById(imId, {dst.x, dst.y, dst.z, dst.w}, an, FlipMode::VERTICAL);
gfx->drawImageById(alf, {400,400,400,400}, an, FlipMode::VERTICAL);
        gfx->drawRect({50, 50, 50, 50}, {0.0f, 1.0f, 1.0f, 0.5f});
        gfx->drawLine({100, 100}, {100, 500}, {1.0f, 0.0f, 0.0f, 1.0});
        gfx->drawRectOutline({500, 500, 200, 100}, {0.0f, 0.0f, 1.0f, 1.0f});
        gfx->drawTextById(helloText, {100, 100, 0, 0});
        gfx->drawTextById(ft, {0, 0, 0, 0});
        gfx->endFrame();
      }
    });


InputKey KeyW {.keyId=KeyId::W, .type=DeviceType::Keyboard};
InputKey KeyA {.keyId=KeyId::A, .type=DeviceType::Keyboard};
InputKey KeyS {.keyId=KeyId::S, .type=DeviceType::Keyboard};
InputKey KeyD {.keyId=KeyId::D, .type=DeviceType::Keyboard};
input->setKeyId(KeyW);
input->setKeyId(KeyA);
input->setKeyId(KeyS);
input->setKeyId(KeyD);
ActionManager actionManager;
actionManager.actions["moveUp"] = InputAction{"moveUp", {KeyW}};
actionManager.actions["moveLeft"] = InputAction{"moveLeft", {KeyA}};
actionManager.actions["moveDown"] = InputAction{"moveDown", {KeyS}};
actionManager.actions["moveRight"] = InputAction{"moveRight", {KeyD}};
auto moveWASD = [&]()
{
    if (actionManager.IsActive("moveUp", input)) { dst.y -= 15; }
    if (actionManager.IsActive("moveLeft", input)) { dst.x -= 15; }
    if (actionManager.IsActive("moveDown", input)) { dst.y += 15; }
    if (actionManager.IsActive("moveRight", input)) { dst.x += 15; }
};

InputKey MouseL {.keyId=KeyId::MouseLeft, .type=DeviceType::Mouse};
input->setKeyId(MouseL);

eventDispatcher->subscribe("Click LMouse", [](Event e){std::cout << "Event: " << e.type << std::endl;});
    bool runnind = 1;
    while (runnind) {
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
      runnind = input->pollEvents();
      // window->renderFrame();
      moveWASD();
      if (input->getKeyState(MouseL)) { float x,y; input->getMousePosition(x, y); std::cout << "x." << x << " y." << y << std::endl; eventDispatcher->dispatch(Event{"Click LMouse"});}
   }
    runningRender = 0;
    renderThread.join();
    window->destroyWindow();
    platform->shutdown();

  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    std::cin.get();
  }
  return 0;
}
