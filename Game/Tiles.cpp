#include "Tiles.h"
#include "MiniginEngine.h"

dae::Tile::Tile(GameObject * pOwner)
	: BaseComponent(pOwner)
{
}

dae::WallTile::WallTile(GameObject* pOwner)
	: Tile(pOwner)
	, m_Hitbox{ pOwner->AttachComponent<HitboxComponent>(m_TileSize, m_TileSize, true) }
	, m_Sprite{ pOwner->AttachComponent<RenderComponent>() }
{
	m_Sprite.LoadTexture("Sprites/Wall.png");
}

bool dae::WallTile::IsAccessible() const
{
	return true;
}

dae::TeleportTile::TeleportTile(GameObject* pOwner)
	: Tile(pOwner)
	, m_Hitbox{ pOwner->AttachComponent<HitboxComponent>(m_TileSize, m_TileSize, true) }
	, m_Sprite{ pOwner->AttachComponent<RenderComponent>() }
{
	m_Sprite.LoadTexture("Sprites/EnemyTank.png");
}

bool dae::TeleportTile::IsAccessible() const
{
	return true;
}

dae::PathTile::PathTile(GameObject* pOwner)
	: Tile(pOwner)
	, m_Sprite{ pOwner->AttachComponent<RenderComponent>() }
{
	m_Sprite.LoadTexture("Sprites/Path.png");
}

bool dae::PathTile::IsAccessible() const
{
	return false;
}