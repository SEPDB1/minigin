#pragma once
#include "InputUtility.h"

namespace dae
{
	class InputDevice
	{
	public:
		virtual ~InputDevice() = default;
		InputDevice(const InputDevice& other) = delete;
		InputDevice(InputDevice&& other) = delete;
		InputDevice& operator=(const InputDevice& other) = delete;
		InputDevice& operator=(InputDevice&& other) = delete;

		virtual void Update() = 0;

		virtual bool IsButtonCompatible(const Button& button) const = 0;

		virtual bool IsDownThisFrame(const Button& button) const = 0;
		virtual bool IsUpThisFrame(const Button& button) const = 0;
		virtual bool IsPressed(const Button& button) const = 0;

	protected:
		InputDevice() = default;
	};
}