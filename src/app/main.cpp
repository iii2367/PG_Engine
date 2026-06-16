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
        std::vector<uint32_t> audioId;
        audioId.push_back(audio->addAudio("music/Test1.wav", audioTag));
        audioId.push_back(audio->addAudio("music/Test2.wav", audioTag));
        audioId.push_back(audio->addAudio("music/Test3.wav", audioTag));
        audioId.push_back(audio->addAudio("music/TestStream1.wav", audioTag));
        audio->stopAudioAll();
        int curIndex = 0;

        std::function<void()> playNext;
        playNext = [&]() 
        {
            curIndex = (curIndex + 1) % audioId.size();
            int nextId = audioId[curIndex];
            audio->restartAudioById(nextId);
            audio->setStoppedCallbackById(nextId, playNext);
        };

        int firstId = audioId[curIndex];
        audio->restartAudioById(firstId);
        audio->setStoppedCallbackById(firstId, playNext);

        eventDispatcher->subscribe(EventType::PG_Key_Down_N, [&](Event e) {playNext();});
        eventDispatcher->subscribe(EventType::PG_Key_Down_B, [&](Event e) {curIndex = (curIndex - 1 + audioId.size()) % audioId.size();int prevId = audioId[curIndex];audio->restartAudioById(prevId);audio->setStoppedCallbackById(prevId, playNext);});

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
