#pragma once
#include "InputUtility.h"
#include <vector>

namespace dae
{
	class InputDevice;

	class InputAction
	{
	public:
		virtual ~InputAction() = default;

		virtual InputContext GetActionContext(const InputDevice* pDevice) const = 0;

	protected:
		InputAction() = default;
		static float GetButtonValue(const Button& button, const InputDevice* pDevice);
	};

	class InputActionButton final : public InputAction
	{
	public:
		explicit InputActionButton(const Button& button);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:
		Button m_Button{};
	};

	class InputActionAxis2D final : public InputAction
	{
	public:
		InputActionAxis2D() = default;
		InputActionAxis2D(const Button& left, const Button& right, const Button& up, const Button& down);
		InputActionAxis2D(const Axis& axis);

		InputContext GetActionContext(const InputDevice* pDevice) const override;

	private:

		Button m_LeftButton{};
		Button m_RightButton{};
		Button m_UpButton{};
		Button m_DownButton{};
		Axis m_Axis{};
		bool m_UsesButtons{};
	};
}