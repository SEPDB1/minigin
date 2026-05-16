#pragma once
#include <unordered_map>
#include <vector>
#include "BaseComponent.h"
#include "InputTypes.h"

namespace dae
{
	class GameObject;
	class InputDevice;
	class PlayerInputComponent final : public BaseComponent
	{
	public:
		PlayerInputComponent(GameObject* pOwner, InputDeviceID deviceID);
		~PlayerInputComponent() = default;

		PlayerInputComponent(const PlayerInputComponent& other) = delete;
		PlayerInputComponent(PlayerInputComponent&& other) = delete;
		PlayerInputComponent& operator=(const PlayerInputComponent& other) = delete;
		PlayerInputComponent& operator=(PlayerInputComponent&& other) = delete;

		void Update() override;

		void BindAction(InputActionID action);
		void BindAction(const std::vector<InputActionID>& actions);

		void EraseAction(InputActionID action);

	private:
		std::vector<InputActionID> m_ActionsIDs{};
		InputDeviceID m_DeviceID{};
	};
}