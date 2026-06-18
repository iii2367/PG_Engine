#include "../engine/Engine.h"
#include "Module.h"
#include <iostream>
#include <stdexcept>
#include <thread>

int main(int argc, char *argv[])
{
    try 
    {
        Utils::Module<Engine> engine;
        engine.load("Engine.dll", "getClass", "destroyClass");
        engine->init(EngineInitInfo::isBasePlatform 
                    | EngineInitInfo::isWindowPlatform 
                    | EngineInitInfo::isInputPlatform 
                    | EngineInitInfo::isAudioPlatform 
                    | EngineInitInfo::isEventDispatcher 
                    | EngineInitInfo::isGFXAdapter
        );

        auto platform = engine->getPlatform();
        auto base = engine->getPlatform()->getBase();
        auto window = engine->getPlatform()->getWindow();
        auto input = engine->getPlatform()->getInput();
        auto audio = engine->getPlatform()->getAudio();
        auto eventDispatcher = engine->getEventDispatcher();
        auto gfx = engine->getGFXAdapter();

        base->init();
        audio->initAudio();

        WindowInfo winInfo{};
        winInfo.decorated = 1;
        winInfo.resizable = 1;
        window->createWindow(winInfo);
         
        std::string audioTag = "Music";
        auto id1 = audio->addAudioStream("music/TestStream1.wav", audioTag);
        audio->loopAudioById(id1);
        
        auto handle = window->getWindowHandle();
        if(!gfx->init(handle, true)) { throw std::runtime_error("failed to init gfx"); }
        Vec4 dst{400,300,200,200};
        int imId = gfx->loadImage("image/image1.png");
        std::cout << imId << '\n';
        
        auto deviceCount = gfx->getRenderDevices();
        for (auto device : deviceCount)
        {
            std::cout << device.index << '\t' << device.name << '\n';
        }

        int fontId = gfx->loadFont("font/ChelseaMarket.ttf",22);
        int helloText = gfx->createText(fontId, "Hello World", {0,0,0,0});

        bool hi = true;
        eventDispatcher->subscribe(EventType::PG_Key_Down_D, [&](const Event& e){dst.x += 5;});
        eventDispatcher->subscribe(EventType::PG_Key_Down_A, [&](const Event& e){dst.x -= 5;});
        eventDispatcher->subscribe(EventType::PG_Key_Down_S, [&](const Event& e){dst.y += 5;});
        eventDispatcher->subscribe(EventType::PG_Key_Down_W, [&](const Event& e){dst.y -= 5;});
        eventDispatcher->subscribe(EventType::PG_Key_Down_Q, [&](const Event& e){if (hi) {hi=false;} else {hi=true;}});
        std::atomic<bool> runningRender{true};
        float an = 0.5;
        std::thread renderThread([&]{while (runningRender)
        { 
            an+=1;
            gfx->beginFrame({1.0f,1.0f,1.0f,1.0f});
            //gfx->drawRect({50,50,50,50}, {0.0f,1.0f,1.0f,1.0f});
            if (hi){gfx->drawImageById(imId, {dst.x, dst.y, dst.z, dst.w}, an, FlipMode::VERTICAL);}
            gfx->drawRect({50,50,50,50}, {0.0f,1.0f,1.0f,0.5f});
            gfx->drawLine({100,100}, {100,500}, {1.0f, 0.0f, 0.0f, 1.0});
            gfx->drawRectOutline({500,500,200,100}, {0.0f,0.0f,1.0f,1.0f});
            gfx->drawTextById(helloText,{100,100,0,0});
            gfx->endFrame();}
        });
        
        bool runnind = 1;
        while (runnind)
        {
            base->update(16);
            runnind = input->pollEvents(*eventDispatcher);
            //window->renderFrame(); 
        }
        runningRender = 0;
        renderThread.join(); 
        window->destroyWindow();
        base->shutdown();

    } catch (std::runtime_error &e) 
    {
        std::cout << e.what() << std::endl;
        std::cin.get();
    }
  return 0;
}
