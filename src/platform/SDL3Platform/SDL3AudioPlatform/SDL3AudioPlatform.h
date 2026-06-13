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
    void playSound(std::string filePath) override;
    void stopAllSounds() override;
    void setVolume(float volume) override;
    
private:
    MIX_Mixer* mixer;
    
    std::unordered_map<std::string, MIX_Audio*> audioCache;
    std::vector<MIX_Track*> tracks;

    float m_volume = 1.0f;

    MIX_Audio* loadAudio(const std::string& path);
    MIX_Track* getFreeTrack();
    void cleanup();
};

#endif
