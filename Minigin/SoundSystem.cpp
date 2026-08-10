#include "SoundSystem.h"
#include "ResourceManager.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <array>
#include <algorithm>

std::unique_ptr<dae::SoundSystem> dae::SoundLocator::m_pSoundSystem{};

#pragma region SDLSoundSystemImpl

class dae::SDLSoundSystem::SDLSoundSystemImpl final
{
public:
	SDLSoundSystemImpl();
	~SDLSoundSystemImpl();

	void Play(const std::string& file, float);

private:
	MIX_Mixer* m_pMixer{};
};

dae::SDLSoundSystem::SDLSoundSystemImpl::SDLSoundSystemImpl()
{
	if (!MIX_Init())
	{
		std::cout << "Failed to initialise SDL_mixer: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("MIX_Init Error: ") + SDL_GetError());
	}

	m_pMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

	if (!m_pMixer)
	{
		std::cout << "Failed to create the mixer: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("MIX_CreateMixerDevice Error: ") + SDL_GetError());
	}
}

dae::SDLSoundSystem::SDLSoundSystemImpl::~SDLSoundSystemImpl()
{
	MIX_DestroyMixer(m_pMixer);

	MIX_Quit();
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::Play(const std::string& file, float)
{
	auto pAudio{ ResourceManager::GetInstance().LoadAudio(file, m_pMixer) };

	if (!MIX_PlayAudio(m_pMixer, pAudio))
	{
		std::cout << "Failed to play the audio: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("MIX_PlayAudio Error: ") + SDL_GetError());
	}
}

#pragma endregion SDLSoundSystemImpl

void dae::NullSoundSystem::Play(const std::string&, float)
{
}

dae::SDLSoundSystem::SDLSoundSystem()
	: m_pImpl{ std::make_unique<SDLSoundSystemImpl>() }
{
}

dae::SDLSoundSystem::~SDLSoundSystem() = default;

void dae::SDLSoundSystem::Play(const std::string& file, float volume)
{
	m_pImpl->Play(file, volume);
}

dae::SoundSystem& dae::SoundLocator::GetSoundSystem()
{
	return *m_pSoundSystem;
}
