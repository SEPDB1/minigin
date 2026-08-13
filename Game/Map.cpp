#include "Map.h"
#include "ResourceManager.h"
#include "Tiles.h"
#include <fstream>
#include "SdbmHash.h"
#include "SceneManager.h"

dae::Map::Map(const std::string& fileName)
	: m_pTiles{}
{
	LoadMap(fileName);
}

dae::Map::~Map() = default;

void dae::Map::LoadMap(const std::string& fileName)
{
	auto TileTypes{ dae::ResourceManager::GetInstance().ParseData<std::array<uint32_t, m_NrTiles>>(fileName) };
	auto& scene{ SceneManager::GetInstance().GetActiveScene() };

	for (auto idx{ 0 }; idx < TileTypes.size(); ++idx)
	{
		const uint32_t colIdx{ idx % m_WidthGrid };
		const uint32_t rowIdx{ idx / m_WidthGrid };
		auto& pTile{ m_pTiles[idx] };

		switch (TileTypes[idx])
		{
		case MakeSdbmHash("Wall"):
			pTile = std::addressof(scene.AddObject().AttachComponent<WallTile>());
			break;
		case MakeSdbmHash("Path"):
			pTile = std::addressof(scene.AddObject().AttachComponent<PathTile>());
			break;
		case MakeSdbmHash("Teleporter"):
			pTile = std::addressof(scene.AddObject().AttachComponent<TeleportTile>());
			break;
		}

		const glm::vec2 pos{ static_cast<float>(colIdx) * m_TileSize + 16.f, static_cast<float>(rowIdx) * m_TileSize + 16.f };
		m_pTiles[idx]->GetOwner()->SetPosition(pos).SetScale(glm::vec2(2.f, 2.f));

		m_AccessibilityTiles[idx] = pTile->IsAccessible();
	}
}
