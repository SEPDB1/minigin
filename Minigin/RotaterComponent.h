#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class RotaterComponent final : public BaseComponent
	{
	public:
		RotaterComponent(GameObject* pOwner);
		~RotaterComponent() = default;
		RotaterComponent(const RotaterComponent& other) = delete;
		RotaterComponent(RotaterComponent&& other) = delete;
		RotaterComponent& operator=(const RotaterComponent& other) = delete;
		RotaterComponent& operator=(RotaterComponent&& other) = delete;

		void Render() const override;
		void Update() override;

		RotaterComponent& SetRotationSpeed(float speed);

	private:
		float m_RotationSpeed{ 1.f };
	};
}
