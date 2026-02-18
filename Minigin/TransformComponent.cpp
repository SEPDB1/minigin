#include "TransformComponent.h"

dae::TransformComponent::TransformComponent() = default;

dae::TransformComponent::~TransformComponent() = default;

const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::TransformComponent::SetPosition(const glm::vec3& position) 
{ 
	m_Position = position; 
}