#ifndef IAUDIOPLATFORM_H
#define IAUDIOPLATFORM_H

#include <string>

enum class AudioChannel
{
    SFX,
    UI,
    Music,
    Ambient
};

struct IAudioPlatform
{
    virtual ~IAudioPlatform() = default;

    virtual bool initAudio() = 0;
    virtual void stopAllSounds() = 0;
    virtual int playSound(const std::string& path) = 0;
    virtual void pause(int id) = 0;
    virtual void resume(int id) = 0;
    virtual void stop(int id) = 0;
    virtual void setVolume(float v) = 0;
};

#endif
