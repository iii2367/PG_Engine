#include "SDL3BasePlatform.h"

#include <SDL3/SDL.h>
#include <iostream>

bool SDL3BasePlatform::init()
{
    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result != 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }
    printf("SDL_Init success\n");
    return true;
    //return SDL_Init(SDL_INIT_VIDEO /*| SDL_INIT_AUDIO*/) == 0;
}

void SDL3BasePlatform::update()
{
    SDL_Delay(16);
}

void SDL3BasePlatform::shutdown()
{
    SDL_Quit();
}



