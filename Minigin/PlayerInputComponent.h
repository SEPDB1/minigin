#pragma once
#include <unordered_map>
#include <memory>
#include <string>
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

		template <typename CommandT> requires std::derived_from<CommandT, Command>
		void AddCommandBinding(const std::string& actionName, std::unique_ptr<CommandT> pCommand)
		{
			assert(pCommand != nullptr && "Command is a nullptr");
			m_CommandBindingTable.insert_or_assign(actionName, std::move(pCommand));
		}

		void RemoveCommandBinding(const std::string& actionName)
		{
			m_CommandBindingTable.erase(actionName);
		}

	private:
		std::unordered_map<std::string, std::unique_ptr<Command>> m_CommandBindingTable{};
		const InputDevice* m_pDevice{};
	};
}