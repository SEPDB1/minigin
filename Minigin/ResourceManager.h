#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"

struct MIX_Mixer;
struct MIX_Audio;

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		~ResourceManager();
		void Init(const std::filesystem::path& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, uint8_t size);
		MIX_Audio* LoadAudio(const std::string& file, MIX_Mixer* mixer);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

		void UnloadUnusedResources();

		std::filesystem::path m_DataPath;
		std::map<std::string, std::shared_ptr<Texture2D>> m_LoadedTextures{};
		std::map<std::pair<std::string, uint8_t>, std::shared_ptr<Font>> m_LoadedFonts{};
		std::map<std::string, MIX_Audio*> m_LoadedAudio{};
	};
}
