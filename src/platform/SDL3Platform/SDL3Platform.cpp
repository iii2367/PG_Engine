#include "SDL3Platform.h"
#include "SDL3AudioPlatform/SDL3AudioPlatform.h"
#include "SDL3BasePlatform/SDL3BasePlatform.h"
#include "SDL3InputPlatform/SDL3InputPlatform.h"
#include "SDL3WindowPlatform/SDL3WindowPlatform.h"
#include <stdexcept>

SDL3Platform::~SDL3Platform()
{
    if (base) { delete base; }
    if (window) { delete window; }
    if (input) { delete input; }
    if (audio) { delete audio; }
}

void SDL3Platform::createBasePlatform() { if (this->base) { throw std::runtime_error("basePlatform already created."); } this->base = new SDL3BasePlatform();  }
void SDL3Platform::createWindowPlatform() { if (this->window) { throw std::runtime_error("windowPlatform already created."); } this->window = new SDL3WindowPlatform(); }
void SDL3Platform::createInputPlatform() { if (this->input) { throw std::runtime_error("inputPlatform already created."); } this->input = new SDL3InputPlatform(); }
void SDL3Platform::createAudioPlatform() { if (this->audio) { throw std::runtime_error("audioPlatform already created."); } this->audio = new SDL3AudioPlatform(); }


IBasePlatform* SDL3Platform::getBase() const { return this->base; } 
IWindowPlatform* SDL3Platform::getWindow() const { return this->window; }
IInputPlatform* SDL3Platform::getInput() const { return this->input; }
IAudioPlatform* SDL3Platform::getAudio() const { return this->audio; }

extern "C" __declspec(dllexport) IPlatform* getClass() { return new SDL3Platform(); }
extern "C" __declspec(dllexport) void destroyClass(IPlatform* ptr) { delete ptr; }

