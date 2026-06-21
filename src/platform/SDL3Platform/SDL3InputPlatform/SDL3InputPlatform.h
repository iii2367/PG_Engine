#ifndef SDL3INPUTPLATFORM_H
#define SDL3INPUTPLATFORM_H

#include "../../IInputPlatform.h"

#include <SDL3/SDL.h>

class SDL3InputPlatform : public IInputPlatform 
{
public:
    void setKeyId(InputKey& key) override;
    bool getKeyState(const InputKey& key) override;
    bool pollEvents() override;
    void getMousePosition(float &x, float &y) override;
};

#endif
