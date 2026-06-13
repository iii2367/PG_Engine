#ifndef SDL3WINDOWPLATFORM_H
#define SDL3WINDOWPLATFORM_H

#include "../../IWindowPlatform.h"

#include <SDL3/SDL.h>

class SDL3WindowPlatform : public IWindowPlatform
{
public:
    SDL_Window* window = nullptr;
    SDL_Renderer *render = nullptr;

    bool createWindow(int width, int height, std::string title) override;
    void destroyWindow() override;
    void renderFrame() override;
    void setTitle(std::string title) override;
    void resize(int width, int height) override;
};

#endif
