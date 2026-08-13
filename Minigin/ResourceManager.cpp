#include "ResourceManager.h"
#include <stdexcept>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "Audio.h"
#include "Mixer.h"

namespace fs = std::filesystem;

dae::ResourceManager::~ResourceManager()
{
	MIX_Quit();
	TTF_Quit();
}

void dae::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_DataPath = dataPath;

	if (!TTF_Init())
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}

	if (!MIX_Init())
	{
		throw std::runtime_error(std::string("Failed to load support for audio: ") + SDL_GetError());
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

std::shared_ptr<dae::Audio> dae::ResourceManager::LoadAudio(const std::string& file, MIX_Mixer* pMixer)
{
	const auto fullPath = m_DataPath / file;
	const auto filename = fs::path(fullPath).filename().string();

	if (m_LoadedAudio.find(filename) == m_LoadedAudio.end())
	{
		m_LoadedAudio.insert(std::pair(filename, std::make_shared<Audio>(fullPath.string(), pMixer)));
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
