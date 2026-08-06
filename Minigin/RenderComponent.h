#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"
#include <unordered_map>
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		enum class Pivot
		{
			topLeft,
			top,
			topRight,
			right,
			bottomRight,
			bottom,
			bottomLeft,
			left,
			center
		};

		RenderComponent(GameObject* pOwner, Pivot pivot = Pivot::center);
		~RenderComponent();
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Render() const override;
		void Update() override;

		std::shared_ptr<Texture2D> LoadTexture(const std::string& path);

		void SetPivot(Pivot newPivot);

		Texture2D* GetTexture() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		Pivot m_Pivot;

		const static std::unordered_map<Pivot, glm::vec2> m_OffsetTable;
	};
}