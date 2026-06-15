#include "SDL3BasePlatform.h"

#include <SDL3/SDL.h>

bool SDL3BasePlatform::init()
{
    return SDL_Init(SDL_INIT_VIDEO); 
}

void SDL3BasePlatform::update(int ms)
{
    SDL_Delay(ms);
}

void SDL3BasePlatform::shutdown()
{
    SDL_Quit();
}



