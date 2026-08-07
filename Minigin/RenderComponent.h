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
		enum class PivotType
		{
			center,
			topLeft,
			top,
			topRight,
			right,
			bottomRight,
			bottom,
			bottomLeft,
			left,
			custom
		};

		RenderComponent(GameObject* pOwner, PivotType pivot = PivotType::center);
		RenderComponent(GameObject* pOwner, const glm::vec2& customPivot);
		~RenderComponent();
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Render() const override;
		void Update() override;

		std::shared_ptr<Texture2D> LoadTexture(const std::string& path);

		/// Lets you set the pivot by selecting a type from PivotType.
		/// Do not use this function if you want a custom pivot, use SetCustomPivot instead.
		void SetPivot(PivotType type);

		/// Lets you set a custom pivot.
		/// (0, 0) is the topLeft corner of the texture, (1, 1) is the bottomRight corner. 
		void SetCustomPivot(const glm::vec2& customPivot);

		Texture2D* GetTexture() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		glm::vec2 m_Pivot{};
		PivotType m_PivotType{};

		const static std::unordered_map<PivotType, glm::vec2> m_PivotTable;
	};
}