#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class RenderComponent;
	class Grid final : public BaseComponent
	{
	public:
		Grid(GameObject* pOwner);
		~Grid() = default;
		Grid(const Grid& other) = delete;
		Grid(Grid&& other) = delete;
		Grid& operator=(const Grid& other) = delete;
		Grid& operator=(Grid&& other) = delete;

		void Start() override;
		void Render() const override {}
		void Update() override {}

	private:
		GameObject& m_BgObj;
		RenderComponent& m_BgSprite;

		inline static const float m_TileSize{ 16.f };
		inline static const float m_Scale{ 4.f };
	};
}