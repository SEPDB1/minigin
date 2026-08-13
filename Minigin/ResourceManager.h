#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"
#include <nlohmann/json.hpp>

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

		template <typename T>
		T ParseData(const std::string& jsonFile)
		{
			const auto fullname = m_DataPath / jsonFile;
			const auto filename = std::filesystem::path(fullname).filename().string();
			std::ifstream f(fullname);

			if (!f.is_open())
				throw std::runtime_error("Could not open file: " + jsonFile);

			try
			{
				return nlohmann::json::parse(f).get<T>();
			}
			catch (const nlohmann::json::exception& e)
			{
				throw std::runtime_error("JSON parse error in " + jsonFile + ": " + e.what());
			}
		}

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
