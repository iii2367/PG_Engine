#ifndef SDL3AUDIOPLATFORM_H
#define SDL3AUDIOPLATFORM_H

#include "../../IAudioPlatform.h"

#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <unordered_map>

class SDL3AudioPlatform : public IAudioPlatform
{
public:
    ~SDL3AudioPlatform();

    bool initAudio() override;

    int playSound(const std::string& filePath) override;
    void stop(int handle) override;
    void pause(int handle) override;
    void resume(int handle) override;

    void stopAllSounds() override;
    void setVolume(float volume) override;
private:
    struct SoundInstance
    {
        MIX_Track* track = nullptr;
        MIX_Audio* audio = nullptr;
        bool paused = false;
        bool active = false;
    };

    MIX_Mixer* mixer = nullptr;
    
    std::unordered_map<std::string, MIX_Audio*> audioCache;
    std::unordered_map<int, SoundInstance*> handleMap;
    std::vector<SoundInstance> instances;

    float m_volume = 1.0f;

    int nextHandle = 1;

    SoundInstance* findInstance(int handle);
    MIX_Audio* loadAudio(const std::string& path);
    MIX_Track* getFreeTrack();
};

#endif
