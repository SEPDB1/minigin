#pragma once
#include <unordered_map>
#include <memory>
#include "BaseComponent.h"
#include "Command.h"

namespace dae
{
	class GameObject;
	class InputDevice;
	class InputAction;
	class PlayerInputComponent final : public BaseComponent
	{
	public:
		PlayerInputComponent(GameObject* pOwner, const InputDevice* pDevice);
		~PlayerInputComponent() = default;

		PlayerInputComponent(const PlayerInputComponent& other) = delete;
		PlayerInputComponent(PlayerInputComponent&& other) = delete;
		PlayerInputComponent& operator=(const PlayerInputComponent& other) = delete;
		PlayerInputComponent& operator=(PlayerInputComponent&& other) = delete;

		void Render() const override;
		void Update() override;

		void AddInputAction(const InputAction* pAction);
		void DeleteInputAction(const InputAction* pActionToDelete);

		// Overwrites the current command binded to pAction
		template <typename CommandT> requires std::derived_from<CommandT, Command>
		void AddCommandBinding(const InputAction* pAction, std::unique_ptr<CommandT>&& pCommand)
		{
			m_CommandBindingTable.insert_or_assign(pAction, std::move(pCommand));
		}

	private:
		std::unordered_map<const InputAction*, std::unique_ptr<Command>> m_CommandBindingTable{};
		const InputDevice* m_pDevice{};
	};
}