#pragma once
#include <glm/vec2.hpp>

namespace dae
{
	class HitboxComponent;

	struct Rect
	{
		Rect() = default;
		Rect(float left, float top, float width, float height);

		bool IsOverlapping(const Rect& r) const;
		glm::vec2 GetCollisionNormal(const glm::vec2& point) const;
		glm::vec2 GetCenter() const;

		float left{};
		float top{};
		float width{};
		float height{};
	};

	struct CollisionInfo
	{
		CollisionInfo() = default;
		CollisionInfo(const glm::vec2& surfaceNormal, const HitboxComponent* pCollider);

		glm::vec2 surfaceNormal{};
		const HitboxComponent* pCollider{};
	};
}