#include "Audio.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

dae::Audio::Audio(const std::string& path, MIX_Mixer* pMixer)
	: m_pAudio{ MIX_LoadAudio(pMixer, path.c_str(), false)}
{
	if (!m_pAudio)
	{
		std::cout << "Failed to create audio: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("MIX_LoadAudio Error: ") + SDL_GetError());
	}
}

dae::Audio::~Audio()
{
	MIX_DestroyAudio(m_pAudio);
}

MIX_Audio* dae::Audio::GetAudio() const
{
	return m_pAudio;
}
