#include "SDL3AudioPlatform.h"

#include <iostream>
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>

// https://github.com/libsdl-org/SDL/blob/main/examples/audio/01-simple-playback/simple-playback.c
SDL3AudioPlatform::~SDL3AudioPlatform()
{
    cleanup();
}

bool SDL3AudioPlatform::initAudio()
{
    if (!SDL_Init(SDL_INIT_AUDIO))
    {
puts("1");
        return false;
    }

    if (!MIX_Init()) { puts("2"); return false; }

    SDL_AudioSpec spec{};
    spec.freq = 48000;
    spec.format = SDL_AUDIO_F32;
    spec.channels = 2;
    mixer = MIX_CreateMixer(&spec);

    if (!mixer) { puts("3"); MIX_Quit();
        SDL_Quit();
 return false; }

    // створюємо пул треків
    for (int i = 0; i < 32; i++)
    {
        MIX_Track* t = MIX_CreateTrack(mixer);
        tracks.push_back(t);
    }

    MIX_SetMixerGain(mixer, m_volume);

    return true;
}
    
void SDL3AudioPlatform::playSound(std::string filePath)
{
    if (!mixer) { return; }

    MIX_Audio* audio = loadAudio(filePath);
    if (!audio) { return; }

    MIX_Track* track = getFreeTrack();
    if (!track) { return; }

    MIX_SetTrackAudio(track, audio);
    MIX_PlayTrack(track, 0);
}

void SDL3AudioPlatform::stopAllSounds()
{
    if (mixer) { MIX_StopAllTracks(mixer, 0); }
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

MIX_Track* SDL3AudioPlatform::getFreeTrack()
{
    for (auto* t : tracks)
    {
        if (!MIX_TrackPlaying(t)) { return t; }
    }
    return nullptr;
}

void SDL3AudioPlatform::cleanup()
{
    for (auto& [k, v] : audioCache) { MIX_DestroyAudio(v); }

    audioCache.clear();

    for (auto* t : tracks) { MIX_DestroyTrack(t); }

    tracks.clear();

    if (mixer) { MIX_DestroyMixer(mixer); }

    MIX_Quit();
}
