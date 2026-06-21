#ifndef IPLATFORM_H
#define IPLATFORM_H

#include "IInputPlatform.h"
#include "IWindowPlatform.h"
#include "IAudioPlatform.h"

struct IPlatform {
    virtual ~IPlatform() = default;

    virtual bool init() = 0;
    virtual void shutdown() = 0;

    virtual IWindowPlatform* getWindow() const = 0;
    virtual IInputPlatform* getInput() const = 0;
    virtual IAudioPlatform* getAudio() const = 0;
};

#endif
