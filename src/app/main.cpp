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
        gfx->init(handle);
        std::string imTag = "Player";
        Vec4 dst{400,300,50,50};
        int imId = gfx->addImage("image/image1.png", imTag, {dst.x,dst.y,dst.z,dst.w});
        std::cout << imId << '\n';
        eventDispatcher->subscribe(EventType::PG_Key_Down_W, [&](const Event& e){dst.x += 5;});
        eventDispatcher->subscribe(EventType::PG_Key_Down_S, [&](const Event& e){dst.x -= 5;});
        std::atomic<bool> runningRender{true};
        std::thread renderThread([&]{while (runningRender){ gfx->renderFrameBegin(); gfx->drawImageById(imId, dst); gfx->renderFrameEnd();}});
        
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
