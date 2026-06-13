#include "SDL3AudioPlatform.h"

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

SDL3AudioPlatform::~SDL3AudioPlatform()
{
    
}

bool SDL3AudioPlatform::initAudio()
{
    if (!MIX_Init()) { return false; }
    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

    if (!mixer) { return false; }

    for (int i = 0; i < 32; i++)
    {
        SoundInstance inst;
        inst.track = MIX_CreateTrack(mixer);
        instances.push_back(inst);
    }

    MIX_SetMixerGain(mixer, m_volume);
    return true;
}
    
int SDL3AudioPlatform::playSound(const std::string& filePath)
{
    MIX_Audio* audio = loadAudio(filePath);
    if (!audio) { return -1; } 

    MIX_Track* track = getFreeTrack();
    if (!track) { return -1; } 

    SoundInstance* inst = nullptr;

    for (auto& i : instances)
    {
        if (!i.active)
        {
            inst = &i;
            break;
        }
    } 
        
    if (!inst) { return -1; }

    inst->audio = audio;
    inst->track = track;
    inst->active = true;
    inst->paused = false;

    MIX_SetTrackAudio(track, audio);
    MIX_PlayTrack(track, 0);

    int handle = nextHandle++;
    handleMap[handle] = inst;

    return handle;
}

void SDL3AudioPlatform::pause(int handle)
{
    SoundInstance* inst = findInstance(handle);
    if (!inst || !inst->track) { return; }

    MIX_PauseTrack(inst->track);
    inst->paused = true;
}

void SDL3AudioPlatform::resume(int handle)
{
    SoundInstance* inst = findInstance(handle);
    if (!inst || !inst->track) { return; }

    MIX_ResumeTrack(inst->track);
    inst->paused = false;
}

void SDL3AudioPlatform::stop(int handle)
{
    SoundInstance* inst = findInstance(handle);
    if (!inst || !inst->track) { return; }

    MIX_StopTrack(inst->track, 0);

    inst->active = false;
    inst->paused = false;

    handleMap.erase(handle);
}

void SDL3AudioPlatform::stopAllSounds()
{
    if (mixer) { MIX_StopAllTracks(mixer, 0); }

    for (auto& i : instances)
    {
        i.active = false;
        i.paused = false;
    }
}
    
void SDL3AudioPlatform::setVolume(float volume)
{
    m_volume = volume;
    if (mixer) { MIX_SetMixerGain(mixer, volume); }
}

MIX_Audio* SDL3AudioPlatform::loadAudio(const std::string& path)
{
    auto it = audioCache.find(path);
    if (it != audioCache.end()) { return it->second; }

    MIX_Audio* audio = MIX_LoadAudio(mixer, path.c_str(), true);
    if (!audio) { return nullptr; }

    audioCache[path] = audio;
    return audio;
}

SDL3AudioPlatform::SoundInstance* SDL3AudioPlatform::findInstance(int handle)
{
    auto it = handleMap.find(handle);
    if (it == handleMap.end()) { return nullptr; }

    return it->second;
}

MIX_Track* SDL3AudioPlatform::getFreeTrack()
{
    for (auto& i : instances)
    {
        if (!MIX_TrackPlaying(i.track) && !i.active) { return i.track; }
    }

    return instances[0].track; 
}
