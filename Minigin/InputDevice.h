#pragma once
#include <cstdint>
#include "InputTypes.h"

namespace dae
{
	class InputDevice
	{
	public:
		InputDevice();
		virtual ~InputDevice() = default;
		InputDevice(const InputDevice& other) = delete;
		InputDevice(InputDevice&& other) = delete;
		InputDevice& operator=(const InputDevice& other) = delete;
		InputDevice& operator=(InputDevice&& other) = delete;

		virtual void Update() = 0;

		virtual InputContext GetContext(UButton uButton) const = 0;

		InputDeviceID GetID() const;

	private:
		InputDeviceID m_ID{};

		static inline InputDeviceID m_NextID{ 0 };
	};
}