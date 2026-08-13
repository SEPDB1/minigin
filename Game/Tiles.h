#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class HitboxComponent;
	class RenderComponent;

	class Tile : public BaseComponent
	{
	public:
		virtual ~Tile() = default;
		Tile(const Tile& other) = delete;
		Tile(Tile&& other) = delete;
		Tile& operator=(const Tile& other) = delete;
		Tile& operator=(Tile&& other) = delete;

		virtual bool IsAccessible() const = 0;

		inline constexpr static float m_TileSize{ 16 };

	protected:
		Tile(GameObject* pOwner);
	};

	class WallTile final : public Tile
	{
	public:
		WallTile(GameObject* pOwner);
		~WallTile() = default;
		WallTile(const WallTile& other) = delete;
		WallTile(WallTile&& other) = delete;
		WallTile& operator=(const WallTile& other) = delete;
		WallTile& operator=(WallTile&& other) = delete;

		bool IsAccessible() const override;

	private:
		HitboxComponent& m_Hitbox;
		RenderComponent& m_Sprite;
	};

	class TeleportTile final : public Tile
	{
	public:
		TeleportTile(GameObject* pOwner);
		~TeleportTile() = default;
		TeleportTile(const TeleportTile& other) = delete;
		TeleportTile(TeleportTile&& other) = delete;
		TeleportTile& operator=(const TeleportTile& other) = delete;
		TeleportTile& operator=(TeleportTile&& other) = delete;

		bool IsAccessible() const override;

	private:
		HitboxComponent& m_Hitbox;
		RenderComponent& m_Sprite;
	};

	class PathTile final : public Tile
	{
	public:
		PathTile(GameObject* pOwner);
		~PathTile() = default;
		PathTile(const PathTile& other) = delete;
		PathTile(PathTile&& other) = delete;
		PathTile& operator=(const PathTile& other) = delete;
		PathTile& operator=(PathTile&& other) = delete;

		bool IsAccessible() const override;

	private:
		RenderComponent& m_Sprite;
	};
}