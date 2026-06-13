#include "SDL3WindowPlatform.h"

bool SDL3WindowPlatform::createWindow(int width, int height, std::string title)
{
    // Створення вікна
    window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);
    
    // Створення рендеру
    render = SDL_CreateRenderer(window, nullptr);
    if (!window || !render)
    {
        // при невдачи закриття програми
        SDL_DestroyWindow(window); 
        SDL_Quit();
        return false;
    }
    return true;
}

void SDL3WindowPlatform::destroyWindow()
{
    if (window)
    {
        // знищення вікна
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}   

void SDL3WindowPlatform::renderFrame()
{
    // Рендер вікна
    SDL_SetRenderDrawColor(render, 128, 128, 128, 255);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);
}

void SDL3WindowPlatform::setTitle(std::string title) // Заміна Назви вікна
{
    if (window) { SDL_SetWindowTitle(window, title.c_str()); }
}   

void SDL3WindowPlatform::resize(int width, int height) // Зміна розміру вікна
{
    if (window) { SDL_SetWindowSize(window, width, height); }
}



