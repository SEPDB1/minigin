#pragma once
#include <memory>
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class InputDevice;
	class RenderComponent;
	class PlayerInputComponent;
	class PlayerTankComponent final : public BaseComponent
	{
	public:
		PlayerTankComponent(GameObject* pOwner, const InputDevice* pDevice);
		~PlayerTankComponent() = default;
		PlayerTankComponent(const PlayerTankComponent& other) = delete;
		PlayerTankComponent(PlayerTankComponent&& other) = delete;
		PlayerTankComponent& operator=(const PlayerTankComponent& other) = delete;
		PlayerTankComponent& operator=(PlayerTankComponent&& other) = delete;

		void Start() override;
		void Render() const override;
		void Update() override;

	private:
		RenderComponent& m_RenderComp;
		PlayerInputComponent& m_PlayerInput;
	};
}