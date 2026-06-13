#ifndef SDL3BASEPLATFORM_H
#define SDL3BASEPLATFORM_H

#include "../../IBasePlatform.h"

class SDL3BasePlatform : public IBasePlatform
{
public:
    bool init() override;
    void update() override;
    void shutdown() override;
};

#endif


