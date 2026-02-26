#include "RotaterComponent.h"
#include "Timer.h"
#include "GameObject.h"

dae::RotaterComponent::RotaterComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void dae::RotaterComponent::Update()
{
	const auto owner{ BaseComponent::GetOwner() };
	const float eTime{ Timer::GetInstance().GetElapsedTime() };
	owner->SetRotation(owner->GetTransform().GetRotation() + eTime * m_RotationSpeed);
}

dae::RotaterComponent& dae::RotaterComponent::SetRotationSpeed(float speed)
{
	m_RotationSpeed = speed;
	return *this;
}
