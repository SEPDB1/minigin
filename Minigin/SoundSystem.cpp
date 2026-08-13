#include "SoundSystem.h"
#include "ResourceManager.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <array>
#include <algorithm>
#include "Audio.h"
#include "Mixer.h"

std::unique_ptr<dae::SoundSystem> dae::SoundLocator::m_pSoundSystem{};

#pragma region SDLSoundSystemImpl

class dae::SDLSoundSystem::SDLSoundSystemImpl final
{
public:
	SDLSoundSystemImpl();
	~SDLSoundSystemImpl() = default;

	void Play(const std::string& file);

private:
	std::unique_ptr<Mixer> m_pMixer;
};

dae::SDLSoundSystem::SDLSoundSystemImpl::SDLSoundSystemImpl()
	: m_pMixer{ std::make_unique<Mixer>() }
{
}

void dae::SDLSoundSystem::SDLSoundSystemImpl::Play(const std::string& file)
{
	auto pMixer{ m_pMixer->GetMixer() };
	auto pAudio{ ResourceManager::GetInstance().LoadAudio(file, pMixer) };

	if (!MIX_PlayAudio(pMixer, pAudio->GetAudio()))
	{
		std::cout << "Failed to play the audio: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("MIX_PlayAudio Error: ") + SDL_GetError());
	}
}

#pragma endregion SDLSoundSystemImpl

void dae::NullSoundSystem::Play(const std::string&)
{
}

dae::SDLSoundSystem::SDLSoundSystem()
	: m_pImpl{ std::make_unique<SDLSoundSystemImpl>() }
{
}

dae::SDLSoundSystem::~SDLSoundSystem() = default;

void dae::SDLSoundSystem::Play(const std::string& file)
{
	m_pImpl->Play(file);
}

dae::SoundSystem& dae::SoundLocator::GetSoundSystem()
{
	return *m_pSoundSystem;
}
