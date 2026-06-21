#ifndef IAUDIOPLATFORM_H
#define IAUDIOPLATFORM_H

#include <string>
#include <functional>

struct IAudioPlatform
{
    virtual ~IAudioPlatform() = default;

    virtual bool    initAudio() = 0;
    virtual void    quitAudio() = 0;

    virtual int     addAudio(const std::string& path, std::string& tag) = 0;
    virtual int     addAudioStream(const std::string& path, std::string& tag) = 0;
    virtual bool    removeAudio(int id) = 0;

    virtual bool    pauseAudioById(int id) = 0;
    virtual bool    pauseAudioByTag(std::string& tag) = 0;
    virtual bool    pauseAudioAll() = 0;

    virtual bool    resumeAudioById(int id) = 0;
    virtual bool    resumeAudioByTag(std::string& tag) = 0;
    virtual bool    resumeAudioAll() = 0;

    virtual bool    setVolumeById(int id, float volume = 1.0f) = 0;
    virtual bool    setVolumeByTag(std::string& tag, float volume = 1.0f) = 0;
    virtual bool    setVolumeAll(float volume = 1.0f) = 0;

    virtual bool    restartAudioById(int id) = 0;
    virtual bool    restartAudioByTag(std::string& tag) = 0;
    virtual bool    restartAudioAll() = 0;
    
    virtual bool    stopAudioById(int id) = 0;
    virtual bool    stopAudioByTag(std::string& tag) = 0;
    virtual bool    stopAudioAll() = 0;

    virtual bool    loopAudioById(int id) = 0;
    virtual bool    loopAudioByTag(std::string& tag) = 0;
    virtual bool    loopAudioAll() = 0;

    virtual bool    loopAudioById(int id, int num_loops) = 0;
    virtual bool    loopAudioByTag(std::string& tag, int num_loops) = 0;
    virtual bool    loopAudioAll(int num_loops) = 0;

    virtual bool    stopLoopAudioById(int id) = 0;
    virtual bool    stopLoopAudioByTag(std::string& tag) = 0;
    virtual bool    stopLoopAudioAll() = 0;

    virtual bool    isPlayingById(int id) = 0;
    virtual bool    isFinishedById(int id) = 0;

    using   AudioCallbackHandler = std::function<void()>;
    virtual bool    setStoppedCallbackById(int id, AudioCallbackHandler callbackFunction) = 0;
    virtual bool    setStoppedCallbackByTag(const std::string& tag, const AudioCallbackHandler& callbackFunction) = 0;
};

#endif
