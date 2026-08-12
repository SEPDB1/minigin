#pragma once
#include "BaseComponent.h"
#include <array>
#include <memory>

namespace dae
{
	class GameObject;
	class InputDevice;
	class TextComponent;
	class DeviceSlot;
	class Font;

	// Manages the start behaviour before the game
	class StartScreen final : public BaseComponent
	{
	public:
		StartScreen(GameObject* pGameObject);
		~StartScreen() = default;
		StartScreen(const StartScreen& other) = delete;
		StartScreen(StartScreen&& other) = delete;
		StartScreen& operator=(const StartScreen& other) = delete;
		StartScreen& operator=(StartScreen&& other) = delete;

		void AddDevice(const InputDevice* pDevice);
		void RemoveDevice(const InputDevice* pDevice);
		void ReadyUp(const InputDevice* pDevice);

	private:
		static constexpr uint8_t m_DevicesCount{ 2 };

		std::array<std::pair<const InputDevice*, DeviceSlot*>, m_DevicesCount> m_pActivatedDevices{};
		TextComponent& m_Title;
		std::shared_ptr<Font> m_pFont{};
	};
}