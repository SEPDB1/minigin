#pragma once
#include "InputDevice.h"
#include <unordered_map>
#include <memory>

namespace dae
{
	class Mouse final : public InputDevice
	{
	public:
		~Mouse();
		Mouse(const Mouse& other) = delete;
		Mouse(Mouse&& other) = delete;
		Mouse& operator=(const Mouse& other) = delete;
		Mouse& operator=(Mouse&& other) = delete;

		void Update() override;

		bool IsDownThisFrame(const Button& button) const override;
		bool IsUpThisFrame(const Button& button) const override;
		bool IsPressed(const Button& button) const override;
		glm::vec2 GetAxisValue(Axis axis) const override;
		DeviceType GetType() const override;

	private:
		friend class InputManager;
		Mouse();

		class MouseImpl;
		std::unique_ptr<MouseImpl> m_pImpl{};
	};
}