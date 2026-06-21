#ifndef IINPUTPLATFORM_H
#define IINPUTPLATFORM_H

#include "../core/Key/InputKey.h"

struct IInputPlatform
{
    virtual ~IInputPlatform() = default;

    virtual void setKeyId(InputKey& key) = 0;
    virtual bool getKeyState(const InputKey& key) = 0;

    virtual bool pollEvents() = 0;
    virtual void getMousePosition(float &x, float &y) = 0;
};

#endif
