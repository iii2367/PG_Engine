#ifndef IAUDIOPLATFORM_H
#define IAUDIOPLATFORM_H

#include <string>

struct IAudioPlatform {
  virtual ~IAudioPlatform() = default;

  virtual bool initAudio() = 0;
  virtual void playSound(std::string filePath) = 0;
  virtual void stopAllSounds() = 0;
  virtual void setVolume(float volume) = 0;
};

#endif
