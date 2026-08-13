#pragma once
#include <array>
#include <memory>
#include <string>

namespace dae
{
	class Tile;

	class Map final
	{
	public:
		Map(const std::string& fileName);
		Map(const Map& other) = delete;
		Map(Map&& other) = default;
		Map& operator=(const Map& other) = delete;
		Map& operator=(Map&& other) = default;
		~Map();
	
	private:
		void LoadMap(const std::string& fileName);

		inline constexpr static uint32_t m_TileSize{ 32 };
		inline constexpr static uint32_t m_WidthGrid{ 30 };
		inline constexpr static uint32_t m_HeightGrid{ 28 };
		inline constexpr static uint32_t m_NrTiles{ m_WidthGrid * m_HeightGrid };

		std::array<Tile*, m_NrTiles> m_pTiles{};
		std::array<bool, m_NrTiles> m_AccessibilityTiles{};
	};
}