#include "RotaterComponent.h"
#include "Timer.h"
#include "GameObject.h"

dae::RotaterComponent::RotaterComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void dae::RotaterComponent::Render() const
{
}

void dae::RotaterComponent::Update()
{
	const auto pOwner{ BaseComponent::GetOwner() };
	const float deltaTime{ Timer::GetInstance().GetElapsedTime() };

	pOwner->SetRotation(pOwner->GetTransform().GetRotation() + m_RotationSpeed * deltaTime);
}

dae::RotaterComponent& dae::RotaterComponent::SetRotationSpeed(float speed)
{
	m_RotationSpeed = speed;
	return *this;
}
