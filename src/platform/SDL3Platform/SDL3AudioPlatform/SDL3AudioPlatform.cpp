#include "SDL3AudioPlatform.h"

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

SDL3AudioPlatform::~SDL3AudioPlatform() { quitAudio(); }

/*============================================================================================*/

bool    SDL3AudioPlatform::initAudio() 
{
    if (!MIX_Init()) { return false; }

    SDL_AudioSpec spec{};
    spec.freq = 48000;
    spec.format = SDL_AUDIO_F32;
    spec.channels = 2;

    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr); // другий параметер це спеціальні налаштування частоти наприклад
    if (!mixer) { return false; }

    return (mixer != nullptr);
}
void    SDL3AudioPlatform::quitAudio()
{
    for (auto& [id, e] : entries)
    {
        if (e.track) { MIX_DestroyTrack(e.track); }
        if (e.audio) { MIX_DestroyAudio(e.audio); }
    }

    if (mixer) { MIX_DestroyMixer(mixer); }

    MIX_Quit();
}

/*============================================================================================*/

int     SDL3AudioPlatform::addAudio(const std::string& path, std::string& tag) 
{
    MIX_Audio* audio = MIX_LoadAudio(mixer, path.c_str(), false);
    if (!audio) { return -1; }

    MIX_Track* track = MIX_CreateTrack(mixer);
    if (!track) { return -1; } 
    
    MIX_SetTrackAudio(track, audio);
    
    int id = nextId++;

    entries[id] = { audio, track, tag, false };
    bindTag(id, tag);
    MIX_PlayTrack(track, 0);
    return id;
}
bool    SDL3AudioPlatform::removeAudio(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    if (it->second.track) { MIX_DestroyTrack(it->second.track); }

    if (it->second.audio) { MIX_DestroyAudio(it->second.audio); }

    removeFromTag(id, it->second.tag);

    entries.erase(it);
    return true;
}

/*============================================================================================*/

bool    SDL3AudioPlatform::pauseAudioById(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }
    return MIX_PauseTrack(it->second.track);
}
bool    SDL3AudioPlatform::pauseAudioByTag(std::string& tag) 
{
    bool ok = true;
    for (int id : getIdsByTag(tag)) { ok &= MIX_PauseTrack(entries[id].track); }
    return ok;
}
bool    SDL3AudioPlatform::pauseAudioAll() 
{
    for (auto& [id, e] : entries) { MIX_PauseTrack(e.track); }
    return true;
}

/*============================================================================================*/

bool    SDL3AudioPlatform::resumeAudioById(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }
    return MIX_ResumeTrack(it->second.track);
}
bool    SDL3AudioPlatform::resumeAudioByTag(std::string& tag) 
{
    bool ok = true;
    for (int id : getIdsByTag(tag)) { ok &= MIX_ResumeTrack(entries[id].track); }
    return ok;
}
bool    SDL3AudioPlatform::resumeAudioAll() 
{
    for (auto& [id, e] : entries) { MIX_ResumeTrack(e.track); }
    return true;
}

/*============================================================================================*/

bool    SDL3AudioPlatform::setVolumeById(int id, float volume) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }
    return MIX_SetTrackGain(it->second.track, volume);
}
bool    SDL3AudioPlatform::setVolumeByTag(std::string& tag, float volume) 
{
    bool ok = true;
    for (int id : getIdsByTag(tag)) { ok &= MIX_SetTrackGain(entries[id].track, volume); }
    return ok;
}
bool    SDL3AudioPlatform::setVolumeById(float volume) { return MIX_SetMixerGain(mixer, volume); }

/*============================================================================================*/

bool    SDL3AudioPlatform::restartAudioById(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    MIX_StopTrack(it->second.track, 0);
    return MIX_PlayTrack(it->second.track, 0);
}
bool    SDL3AudioPlatform::restartAudioByTag(std::string& tag) 
{
    bool ok = true;
    for (int id : getIdsByTag(tag)) { ok &= restartAudioById(id); }
    return ok;
}
bool    SDL3AudioPlatform::restartAudioAll() 
{
    for (auto& [id, e] : entries)
    {
        MIX_StopTrack(e.track, 0);
        MIX_PlayTrack(e.track, 0);
    }
    return true;
}

/*============================================================================================*/

bool    SDL3AudioPlatform::stopAudioById(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    return MIX_StopTrack(it->second.track, 0);
}
bool    SDL3AudioPlatform::stopAudioByTag(std::string& tag) 
{
    bool ok = true;
    for (int id : getIdsByTag(tag)) { ok &= stopAudioById(id); }
    return ok;
}
bool    SDL3AudioPlatform::stopAudioAll() 
{
    for (auto& [id, e] : entries)
    {
        MIX_StopTrack(e.track, 0);
    }
    return true;
}

/*============================================================================================*/

bool    SDL3AudioPlatform::loopAudioById(int id) 
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    it->second.isLoop = true;
    return MIX_SetTrackLoops(it->second.track, -1);
}
bool    SDL3AudioPlatform::loopAudioByTag(std::string& tag) 
{
    bool ok = true;
    for (int id : getIdsByTag(tag)) { ok &= loopAudioById(id); }
    return ok;
}
bool    SDL3AudioPlatform::loopAudioAll() 
{
    for (auto& [id, e] : entries)
    {
        e.isLoop = true;
        MIX_SetTrackLoops(e.track, -1);
    }
    return true;
}

/*============================================================================================*/

bool    SDL3AudioPlatform::stopLoopAudioById(int id)
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }

    it->second.isLoop = true;
    return MIX_SetTrackLoops(it->second.track, 0);
}
bool    SDL3AudioPlatform::stopLoopAudioByTag(std::string& tag)
{
    bool ok = true;
    for (int id : getIdsByTag(tag)) { ok &= stopLoopAudioById(id); }
    return ok;
}
bool    SDL3AudioPlatform::stopLoopAudioAll()
{
    for (auto& [id, e] : entries)
    {
        e.isLoop = false;
        MIX_SetTrackLoops(e.track, 0);
    }
    return true;
}

/*============================================================================================*/

bool    SDL3AudioPlatform::isPlayingById(int id)
{
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }
    return MIX_TrackPlaying(it->second.track);
}
bool    SDL3AudioPlatform::isFinishedById(int id) {
    auto it = entries.find(id);
    if (it == entries.end()) { return false; }
    return !MIX_TrackPlaying(it->second.track) && !MIX_TrackPaused(it->second.track);
}

/*============================================================================================*/

void SDL3AudioPlatform::bindTag(int id, const std::string& tag)
{
    tagMap[tag].push_back(id);
}

void SDL3AudioPlatform::removeFromTag(int id, const std::string& tag)
{
    auto& vec = tagMap[tag];
    vec.erase(std::remove(vec.begin(), vec.end(), id), vec.end());
}

std::vector<int> SDL3AudioPlatform::getIdsByTag(const std::string& tag)
{
    if (!tagMap.count(tag)) { return {}; }
    return tagMap[tag];
}
