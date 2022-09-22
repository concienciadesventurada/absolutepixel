#include "Sound.h"

#include <iostream>

ISound::~ISound() {     }

Sound::Sound(std::string filepath)
{
    if (SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength) == nullptr)
    {
        std::cerr << "Sound loading error: " << SDL_GetError() << std::endl;
    }
}

Sound::~Sound()
{
    SDL_FreeWAV(m_waveStart);
    SDL_CloseAudioDevice(m_device);
}

void Sound::PlaySound()
{
    // Queue the audio to play when available contrary to a callback function
    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength);
    SDL_PauseAudioDevice(m_device, 0);  // 0 for false: it is not paused
}

void Sound::StopSound()
{
    SDL_PauseAudioDevice(m_device, 1);  // Now pause it
}

void Sound::SetupDevice()
{
    // Request a reasonable default: active sound device like headphones or speakers
    // Set the device with a boolean for playback (0) or recording (1)
    m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);

    // Troubleshooting message if no device found
    if (0 == m_device)
    {
        std::cerr << "Sound device error: " << SDL_GetError() << std::endl; 
    }

}