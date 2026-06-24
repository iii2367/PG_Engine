#include "../engine/Engine.h"
#include "Module.h"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include "../core/ActionManager/ActionManager.h"
#include "../core/ActionManager/InputAction.h"
#include "../core/GameRender/GameSystem.h"
#include "../core/GameRender/ResourceManager.h"
#include "../core/GameRender/Sprite.h"

int main(int argc, char** argv)
{
    try
    {
        Utils::Module<IEngine> engine;
        engine.load("Engine.dll", "getClass", "destroyClass");
        engine->init();

        auto platform = engine->getPlatform();
        platform->init();
        auto window = engine->getPlatform()->getWindow();
        auto input = engine->getPlatform()->getInput();
        auto audio = engine->getPlatform()->getAudio();
        audio->initAudio();
        auto eventDispatcher = engine->getEventDispatcher();
        auto gfx = engine->getGFXAdapter();
    
        WindowInfo winInfo{};
        winInfo.decorated = true;
        winInfo.resizable = true;
        window->createWindow(winInfo);
    
        std::string audioTag = "Music";
        auto audioId1 = audio->addAudioStream("music/TestStream1.wav", audioTag);
        audio->loopAudioById(audioId1);

        auto handle = window->getWindowHandle();
        if (!gfx->init(handle, true)) { throw std::runtime_error("failed to init gfx"); }

        int imageId1 = gfx->loadImage("image/image1.png");
        Rect dst{400, 300, 200, 200};
        int imageId2 = gfx->loadImage("image/Alf.png");

        int fontId1 = gfx->loadFont("font/ChelseaMarket.ttf", 22);
        int helloTextId1 = gfx->createText(fontId1, "Hello World", {0, 0, 0, 0});
    
        ResourceManager resMan(*gfx);
        Sprite Igun;
        Igun.textureId = resMan.loadTexture("image/igun.png");
        Igun.dst = {0,0,200,200};
        Igun.angle = 0;
        Igun.flip = FlipMode::NONE; 

        SpriteSheet AnimSheet;
        AnimSheet.animationCountY = 2;
        AnimSheet.frameCountX = 8;
        AnimSheet.frameWidth = 108;
        AnimSheet.frameHeight = 140;
        AnimSheet.textureId = resMan.loadTexture("image/Anim.png"); 
        Animation runAnim;
        runAnim.row = 0;
        runAnim.frames = 8;
        runAnim.frameTime = 0.1f;
        runAnim.loop = true;
        AnimatedSprite anim(&AnimSheet);
        anim.play(runAnim);
float anMov = 200;
        std::atomic<bool> runningRender{true};
        std::atomic<int> fps{0};
        Camera camera;
        camera.position = {0,0};
        camera.zoom = 1.0f;
        Rect locRect{0,0,0,0};
        std::thread renderThread([&] 
        {
            using clock = std::chrono::high_resolution_clock;
            auto lastTime = clock::now();
            int frameCount = 0;
            float fpsTimer = 0;
            int ft = gfx->createText(fontId1, "FPS: ~", {0, 0, 0, 0});


            while (runningRender)
            {
                frameCount++;
                auto now = clock::now();
                std::chrono::duration<float> delta = now - lastTime;
                lastTime = now;

                float dt = delta.count();
                if (dt > 0.1f) { dt = 0.1f; }

                fpsTimer += dt;

        if (fpsTimer >= 1.0f)
        {
            fps = frameCount;
            frameCount = 0;
            fpsTimer = 0;

            gfx->updateText(ft, "FPS: " + std::to_string(fps.load()));
        }
                
                float winWidth=800, winHeight=600;
                gfx->beginFrame({1.0f, 1.0f, 1.0f, 1.0f}); 
                locRect = camera.worldToScreen(Igun.dst, winWidth, winHeight);
                gfx->drawImageById(Igun.textureId, locRect, Igun.angle, Igun.flip);
                locRect = camera.worldToScreen(dst, winWidth, winHeight);
                gfx->drawImageById(imageId1, {locRect.x, locRect.y, locRect.w, locRect.h}, 0, FlipMode::NONE);
        
                anim.update(dt);
Rect src = anim.getSourceRect();
        Rect dstAnim = camera.worldToScreen({anMov,200,108,140}, winWidth, winHeight);
anMov += 10;
        gfx->drawImageRegionById(
            AnimSheet.textureId,
            src,
            dstAnim,
            0,
            FlipMode::NONE
        );
                
                locRect = camera.worldToScreen({400,400,400,400}, winWidth, winHeight);
                gfx->drawImageById(imageId2, {locRect.x,locRect.y,locRect.w,locRect.h}, 0, FlipMode::NONE);
                locRect = camera.worldToScreen({100,100,0,0}, winWidth, winHeight);
                gfx->drawTextById(helloTextId1, {locRect.x, locRect.y, locRect.w, locRect.h}); 
                gfx->drawTextById(ft, {0, 0, 0, 0});
                gfx->endFrame();
            }
        });
int t = std::time(0);
        InputKey KeyW {.keyId=KeyId::W, .type=DeviceType::Keyboard};
        InputKey KeyA {.keyId=KeyId::A, .type=DeviceType::Keyboard};
        InputKey KeyS {.keyId=KeyId::S, .type=DeviceType::Keyboard};
        InputKey KeyD {.keyId=KeyId::D, .type=DeviceType::Keyboard};
        InputKey KeyUp {.keyId=KeyId::ArrowUp, .type=DeviceType::Keyboard};
        InputKey KeyDown {.keyId=KeyId::ArrowDown, .type=DeviceType::Keyboard};
        input->setKeyId(KeyW);
        input->setKeyId(KeyA);
        input->setKeyId(KeyS);
        input->setKeyId(KeyD);
        input->setKeyId(KeyUp);
        input->setKeyId(KeyDown);
        ActionManager actionManager;
        actionManager.actions["moveUp"] = InputAction{"moveUp", {KeyW}};
        actionManager.actions["moveLeft"] = InputAction{"moveLeft", {KeyA}};
        actionManager.actions["moveDown"] = InputAction{"moveDown", {KeyS}};
        actionManager.actions["moveRight"] = InputAction{"moveRight", {KeyD}};
        actionManager.actions["zoomUp"] = InputAction{"zoomUp", {KeyUp}};
        actionManager.actions["zoomDown"] = InputAction{"zoomDown", {KeyDown}};
        auto moveWASD = [&]()
        {
            if (actionManager.IsActive("moveUp", input)) { dst.y -= 15; camera.position.y-=15;}
            if (actionManager.IsActive("moveLeft", input)) { dst.x -= 15; camera.position.x-=15;}
            if (actionManager.IsActive("moveDown", input)) { dst.y += 15; camera.position.y+=15;}
            if (actionManager.IsActive("moveRight", input)) { dst.x += 15; camera.position.x+=15;}
            if (actionManager.IsActive("zoomDown", input)) { camera.zoom-=0.005; puts("zoom-");}
            if (actionManager.IsActive("zoomUp", input)) { camera.zoom+=0.005; puts("zoom+");}
        };

        bool runnind = 1;
        while (runnind) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            runnind = input->pollEvents();
            moveWASD();
        }    
        runningRender = 0;
        renderThread.join();
        window->destroyWindow();
        platform->shutdown();

    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        std::cin.get();
    }
    return 0;
}
