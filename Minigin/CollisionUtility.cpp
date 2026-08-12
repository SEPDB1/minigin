#include "CollisionUtility.h"
#include <algorithm>

dae::Rect::Rect(float left, float top, float width, float height)
	: left{ left }
	, top{ top }
	, width{ width }
	, height{ height }
{

}

bool dae::Rect::IsOverlapping(const Rect& r) const
{
	if (r.left + r.width < this->left)
		return false;
	if (this->left + this->width < r.left)
		return false;
	if (r.top + r.height < this->top)
		return false;
	if (this->top + this->height < r.top)
		return false;

	return true;
}

dae::CollisionInfo dae::Rect::CreateCollisionInfo(const glm::vec2& point) const
{
	// Distance from the point to each of the rect's 4 edges
	const float distLeft{ point.x - this->left };
	const float distRight{ this->left + this->width - point.x };
	const float distTop{ point.y - this->top };
	const float distBottom{ this->top + this->height - point.y };

	// The smallest distance is the edge that was hit
	dae::CollisionInfo info{};
	info.distanceToWall = std::min({ distLeft, distRight, distTop, distBottom });

	if (info.distanceToWall == distLeft)
		info.surfaceNormal = { -1.f, 0.f };
	else if (info.distanceToWall == distRight)
		info.surfaceNormal = { 1.f, 0.f };
	else if (info.distanceToWall == distTop)
		info.surfaceNormal = { 0.f, -1.f };
	else
		info.surfaceNormal = { 0.f, 1.f };

	return info;
}

glm::vec2 dae::Rect::GetCenter() const
{
	return glm::vec2{ this->left + this->width / 2.f, this->top + this->height / 2.f };
}

dae::CollisionInfo::CollisionInfo(const glm::vec2& surfaceNormal, const HitboxComponent* pCollider, float distanceToWall)
	: surfaceNormal{ surfaceNormal }
	, pCollider{ pCollider }
	, distanceToWall{ distanceToWall }
{
}
