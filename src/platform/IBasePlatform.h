#ifndef IBASEPLATFORM_H
#define IBASEPLATFORM_H

struct IBasePlatform
{
    virtual ~IBasePlatform() = default;

    virtual bool init() = 0;
    virtual void update(int ms) = 0;
    virtual void shutdown() = 0;
};

#endif
