#ifndef SDL3PLATFORM_H
#define SDL3PLATFORM_H

#include "../IPlatform.h"

#include "SDL3BasePlatform/SDL3BasePlatform.h"
#include "SDL3WindowPlatform/SDL3WindowPlatform.h"
#include "SDL3InputPlatform/SDL3InputPlatform.h"

class SDL3Platform : public IPlatform
{
public:
    ~SDL3Platform();
    void createBasePlatform() override;
    void createWindowPlatform() override;
    void createInputPlatform() override;

    IBasePlatform* getBase() const override;
    IWindowPlatform* getWindow() const override;
    IInputPlatform* getInput() const override;
private:
    SDL3BasePlatform* base = nullptr;
    SDL3WindowPlatform* window = nullptr;
    SDL3InputPlatform* input = nullptr;
};

extern "C" __declspec(dllexport) IPlatform* getClass();
extern "C" __declspec(dllexport) void destroyClass(IPlatform* ptr);

#endif
