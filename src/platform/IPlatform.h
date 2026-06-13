#ifndef IPLATFORM_H
#define IPLATFORM_H

#include "IBasePlatform.h"
#include "IInputPlatform.h"
#include "IWindowPlatform.h"
//#include "IAudioPlatform.h"

struct IPlatform {
    virtual ~IPlatform() = default;

    virtual void createBasePlatform() = 0;
    virtual void createWindowPlatform() = 0;
    virtual void createInputPlatform() = 0;

    virtual IBasePlatform* getBase() const = 0;
    virtual IWindowPlatform* getWindow() const = 0;
    virtual IInputPlatform* getInput() const = 0;
};

#endif
