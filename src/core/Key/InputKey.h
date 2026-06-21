#ifndef INPUTKEY_H
#define INPUTKEY_H

#include "KeyId.h"
#include <any>

enum class DeviceType
{
    Keyboard,
    Mouse,
};

class InputKey
{
public:
    KeyId keyId;
    std::any platformId;
    DeviceType type;
};

#endif
