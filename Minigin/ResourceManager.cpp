#include <stdexcept>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

namespace fs = std::filesystem;

dae::ResourceManager::~ResourceManager()
{
	for (const auto& pair : m_LoadedAudio)
		MIX_DestroyAudio(pair.second);
}

void dae::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_DataPath = dataPath;

	if (!TTF_Init())
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_DataPath/file;
	const auto filename = fs::path(fullPath).filename().string();

	if (m_LoadedTextures.find(filename) == m_LoadedTextures.end())
	{
		auto pTexture = std::make_shared<Texture2D>(fullPath.string());
		m_LoadedTextures.insert(std::pair(filename, pTexture));
	}

	return m_LoadedTextures.at(filename);
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, uint8_t size)
{
	const auto fullPath = m_DataPath/file;
	const auto filename = fs::path(fullPath).filename().string();
	const auto key = std::pair<std::string, uint8_t>(filename, size);
	if(m_LoadedFonts.find(key) == m_LoadedFonts.end())
		m_LoadedFonts.insert(std::pair(key,std::make_shared<Font>(fullPath.string(), size)));
	return m_LoadedFonts.at(key);
}

MIX_Audio* dae::ResourceManager::LoadAudio(const std::string& file, MIX_Mixer* pMixer)
{
	const auto fullPath = m_DataPath / file;
	const auto filename = fs::path(fullPath).filename().string();

	if (m_LoadedAudio.find(filename) == m_LoadedAudio.end())
	{
		const auto pAudio{ MIX_LoadAudio(pMixer, fullPath.string().c_str(), false)};

		if (!pAudio)
		{
			std::cout << "Failed to load in audio: " << SDL_GetError() << "\n";
			throw std::runtime_error(std::string("MIX_LoadAudio Error: ") + SDL_GetError());
		}

		m_LoadedAudio.insert(std::pair(filename, pAudio));
	}

	return m_LoadedAudio.at(filename);
}

void dae::ResourceManager::UnloadUnusedResources()
{
	for (auto it = m_LoadedTextures.begin(); it != m_LoadedTextures.end();)
	{
		if (it->second.use_count() == 1)
			it = m_LoadedTextures.erase(it);
		else
			++it;
	}

	for (auto it = m_LoadedFonts.begin(); it != m_LoadedFonts.end();)
	{
		if (it->second.use_count() == 1)
			it = m_LoadedFonts.erase(it);
		else
			++it;
	}
}
