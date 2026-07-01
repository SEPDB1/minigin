#pragma once
#include "InputUtility.h"

namespace dae
{
	class InputDevice
	{
	public:
		InputDevice() = default;
		virtual ~InputDevice() = default;
		InputDevice(const InputDevice& other) = delete;
		InputDevice(InputDevice&& other) = delete;
		InputDevice& operator=(const InputDevice& other) = delete;
		InputDevice& operator=(InputDevice&& other) = delete;

		virtual void Update() = 0;

		virtual bool IsButtonCompatible(Button button) const = 0;

		virtual bool IsDownThisFrame(Button button) const = 0;
		virtual bool IsUpThisFrame(Button button) const = 0;
		virtual bool IsPressed(Button button) const = 0;
	};
}