#include "Mixer.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

dae::Mixer::Mixer()
	: m_pMixer{ MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr) }
{
	if (!m_pMixer)
	{
		std::cout << "Failed to create the mixer: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("MIX_CreateMixerDevice Error: ") + SDL_GetError());
	}
}

dae::Mixer::~Mixer()
{
	MIX_DestroyMixer(m_pMixer);
}

MIX_Mixer* dae::Mixer::GetMixer() const
{
	return m_pMixer;
}
