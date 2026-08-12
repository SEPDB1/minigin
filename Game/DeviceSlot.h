#pragma once
#include <cstdint>
#include "BaseComponent.h"
#include <array>
#include <utility>
#include <glm/fwd.hpp> 
#include <memory>
#include "Subject.h"

namespace dae
{
	class GameObject;
	class RenderComponent;	
	enum class DeviceType : uint8_t;
	class Font;
	class TextComponent;

	class DeviceSlot final : public BaseComponent
	{
	public:
		enum class Visual : uint8_t
		{
			noDevice,
			keyboard,
			gamepad,
			count
		};

		DeviceSlot(GameObject* pGameObject);
		~DeviceSlot() = default;
		DeviceSlot(const DeviceSlot& other) = delete;
		DeviceSlot(DeviceSlot&& other) = delete;
		DeviceSlot& operator=(const DeviceSlot& other) = delete;
		DeviceSlot& operator=(DeviceSlot&& other) = delete;

		void ChangeImage(Visual image);
		void ChangeImage(DeviceType type);
		void ReadyUp();

	private:
		void DisplayReadyUp();

		std::array<RenderComponent*, std::to_underlying(Visual::count)> m_pSprites{};
		std::shared_ptr<Font> m_pFont{};
		RenderComponent& m_MenuBox;
		TextComponent& m_Title;
		TextComponent& m_Ready;
		TextComponent& m_NotReady;
		Visual m_CurrentVisual{ Visual::noDevice };
		bool m_IsReady{ false };

		inline static uint32_t m_Count{ 0 };
 	};
}