#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL2/SDL.h>

class ISound
{
    public:
        virtual ~ISound();

        virtual void PlaySound() = 0;
        virtual void StopSound() = 0;
};

class Sound : public ISound
{
    public:
        // Constructor
        Sound(std::string filepath);

        // Destructor
        ~Sound();

        // Reproduce and stop sound
        void PlaySound();
        void StopSound();

        // SPECIFIC TO SDL AUDIO API
        void SetupDevice(); // Preferably in its own Audio Manager singleton class

    private:
        //  Device in which will sound audio files. TODO: ALL THIS COULD BE IN THE AUDIO MANAGER.
        SDL_AudioDeviceID m_device;

        // Properties of WAV file loaded
        SDL_AudioSpec m_audioSpec;
        Uint8* m_waveStart;
        Uint32 m_waveLength;
};

#endif