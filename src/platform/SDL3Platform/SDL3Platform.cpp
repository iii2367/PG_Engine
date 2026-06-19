#include "SDL3Platform.h"
#include "SDL3AudioPlatform/SDL3AudioPlatform.h"
#include "SDL3InputPlatform/SDL3InputPlatform.h"
#include "SDL3WindowPlatform/SDL3WindowPlatform.h"

SDL3Platform::~SDL3Platform()
{
    if (window) { delete window; }
    if (input) { delete input; }
    if (audio) { delete audio; }
    SDL_Quit();
}

bool SDL3Platform::init()
{
    window = new SDL3WindowPlatform();
    input = new SDL3InputPlatform();
    audio = new SDL3AudioPlatform();
    return SDL_Init(SDL_INIT_VIDEO); 
}
void SDL3Platform::shutdown()
{
    SDL_Quit();
}

IWindowPlatform* SDL3Platform::getWindow() const { return this->window; }
IInputPlatform* SDL3Platform::getInput() const { return this->input; }
IAudioPlatform* SDL3Platform::getAudio() const { return this->audio; }

extern "C" __declspec(dllexport) IPlatform* getClass() { return new SDL3Platform(); }
extern "C" __declspec(dllexport) void destroyClass(IPlatform* ptr) { delete ptr; }

