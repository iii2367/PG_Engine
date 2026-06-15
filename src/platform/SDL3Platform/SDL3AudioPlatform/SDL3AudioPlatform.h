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
    bool    initAudio() override;
    void    quitAudio() override;

    int     addAudio(const std::string& path, std::string& tag) override;
    int     addAudioStream(const std::string& path, std::string& tag) override;
    bool    removeAudio(int id) override;

    bool    pauseAudioById(int id) override;
    bool    pauseAudioByTag(std::string& tag) override;
    bool    pauseAudioAll() override;

    bool    resumeAudioById(int id) override;
    bool    resumeAudioByTag(std::string& tag) override;
    bool    resumeAudioAll() override;

    bool    setVolumeById(int id, float volume = 1.0f) override;
    bool    setVolumeByTag(std::string& tag, float volume = 1.0f) override;
    bool    setVolumeById(float volume = 1.0f) override;

    bool    restartAudioById(int id) override;
    bool    restartAudioByTag(std::string& tag) override;
    bool    restartAudioAll() override;

    bool    stopAudioById(int id) override;
    bool    stopAudioByTag(std::string& tag) override;
    bool    stopAudioAll() override;

    bool    loopAudioById(int id) override;
    bool    loopAudioByTag(std::string& tag) override;
    bool    loopAudioAll() override;

    bool    loopAudioById(int id, int num_loops) override;
    bool    loopAudioByTag(std::string& tag, int num_loops) override;
    bool    loopAudioAll(int num_loops) override;

    bool    stopLoopAudioById(int id) override;
    bool    stopLoopAudioByTag(std::string& tag) override;
    bool    stopLoopAudioAll() override;

    bool    isPlayingById(int id) override;
    bool    isFinishedById(int id) override;

    bool    setStoppedCallbackById(int id, AudioCallbackHandler callbackFunction) override;
    bool    setStoppedCallbackByTag(const std::string& tag, const AudioCallbackHandler& callbackFunction) override;

private:
    MIX_Mixer* mixer = nullptr; 
    
    struct AudioEntry
    {
        MIX_Audio* audio = nullptr;
        MIX_Track* track = nullptr;
        SDL_AudioStream* stream = nullptr;
        std::string tag;
        bool isLoop = false;
    };

    int nextId = 1;
    std::unordered_map<int, AudioEntry> entries;
    std::unordered_map<std::string, std::vector<int>> tagMap; 
    std::unordered_map<int, AudioCallbackHandler> callbacks;

    void bindTag(int id, const std::string& tag);
    void removeFromTag(int id, const std::string& tag);
    std::vector<int> getIdsByTag(const std::string& tag);
};

#endif
