#include "../engine/Engine.h"
#include "Module.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[])
{
    try 
    {
        Utils::Module<Engine> engine;
        engine.load("Engine.dll", "getClass", "destroyClass");
        engine->init(EngineInitInfo::isBasePlatform | EngineInitInfo::isWindowPlatform | EngineInitInfo::isInputPlatform | EngineInitInfo::isAudioPlatform | EngineInitInfo::isEventDispatcher);

        auto platform = engine->getPlatform();
        auto base = engine->getPlatform()->getBase();
        auto window = engine->getPlatform()->getWindow();
        auto input = engine->getPlatform()->getInput();
        auto audio = engine->getPlatform()->getAudio();
        auto eventDispatcher = engine->getEventDispatcher();

        window->createWindow(800, 600, "PG Engine");

        std::string audioTag = "Music";
        auto id1 = audio->addAudioStream("music/TestStream1.wav", audioTag);
        audio->loopAudioById(id1);
        
        bool runnind = 1;
        while (runnind)
        {
            base->update(16);
            runnind = input->pollEvents(*eventDispatcher);
            window->renderFrame();
        }
        
        window->destroyWindow();
        base->shutdown();

    } catch (std::runtime_error &e) 
    {
        std::cout << e.what() << std::endl;
        std::cin.get();
    }
  return 0;
}
